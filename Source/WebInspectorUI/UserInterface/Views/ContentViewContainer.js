/*
 * Copyright (C) 2013, 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WebInspector.ContentViewContainer = class ContentViewContainer extends WebInspector.View
{
    constructor()
    {
        super();

        this.element.classList.add("content-view-container");

        this._backForwardList = [];
        this._currentIndex = -1;
    }

    // Public

    get currentIndex()
    {
        return this._currentIndex;
    }

    get backForwardList()
    {
        return this._backForwardList;
    }

    get currentContentView()
    {
        if (this._currentIndex < 0 || this._currentIndex > this._backForwardList.length - 1)
            return null;
        return this._backForwardList[this._currentIndex].contentView;
    }

    get currentBackForwardEntry()
    {
        if (this._currentIndex < 0 || this._currentIndex > this._backForwardList.length - 1)
            return null;
        return this._backForwardList[this._currentIndex];
    }

    contentViewForRepresentedObject(representedObject, onlyExisting, extraArguments)
    {
        return WebInspector.ContentView.contentViewForRepresentedObject(representedObject, onlyExisting, extraArguments);
    }

    showContentViewForRepresentedObject(representedObject, extraArguments)
    {
        var contentView = this.contentViewForRepresentedObject(representedObject, false, extraArguments);
        if (!contentView)
            return null;

        this.showContentView(contentView);

        return contentView;
    }

    showContentView(contentView, cookie)
    {
        console.assert(contentView instanceof WebInspector.ContentView);
        if (!(contentView instanceof WebInspector.ContentView))
            return null;

        // ContentViews can be shared between containers. If this content view is
        // not owned by us, it may need to be transferred to this container.
        if (contentView.parentContainer !== this)
            this._takeOwnershipOfContentView(contentView);

        var currentEntry = this.currentBackForwardEntry;
        var provisionalEntry = new WebInspector.BackForwardEntry(contentView, cookie);
        // Don't do anything if we would have added an identical back/forward list entry.
        if (currentEntry && currentEntry.contentView === contentView && Object.shallowEqual(provisionalEntry.cookie, currentEntry.cookie)) {
            const shouldCallShown = false;
            currentEntry.prepareToShow(shouldCallShown);
            return currentEntry.contentView;
        }

        // Showing a content view will truncate the back/forward list after the current index and insert the content view
        // at the end of the list. Finally, the current index will be updated to point to the end of the back/forward list.

        // Increment the current index to where we will insert the content view.
        var newIndex = this._currentIndex + 1;

        // Insert the content view at the new index. This will remove any content views greater than or equal to the index.
        var removedEntries = this._backForwardList.splice(newIndex, this._backForwardList.length - newIndex, provisionalEntry);

        console.assert(newIndex === this._backForwardList.length - 1);
        console.assert(this._backForwardList[newIndex] === provisionalEntry);

        // Disassociate with the removed content views.
        for (var i = 0; i < removedEntries.length; ++i) {
            // Skip disassociation if this content view is still in the back/forward list.
            var shouldDissociateContentView = !this._backForwardList.some(function(existingEntry) {
                return existingEntry.contentView === removedEntries[i].contentView;
            });

            if (shouldDissociateContentView)
                this._disassociateFromContentView(removedEntries[i].contentView, removedEntries[i].tombstone);
        }

        // Associate with the new content view.
        contentView._parentContainer = this;

        this.showBackForwardEntryForIndex(newIndex);

        return contentView;
    }

    showBackForwardEntryForIndex(index)
    {
        console.assert(index >= 0 && index <= this._backForwardList.length - 1);
        if (index < 0 || index > this._backForwardList.length - 1)
            return;

        if (this._currentIndex === index)
            return;

        var previousEntry = this.currentBackForwardEntry;
        this._currentIndex = index;
        var currentEntry = this.currentBackForwardEntry;
        console.assert(currentEntry);

        var isNewContentView = !previousEntry || !currentEntry.contentView.visible;
        if (isNewContentView) {
            // Hide the currently visible content view.
            if (previousEntry)
                this._hideEntry(previousEntry);
            this._showEntry(currentEntry, true);
        } else
            this._showEntry(currentEntry, false);

        this.dispatchEventToListeners(WebInspector.ContentViewContainer.Event.CurrentContentViewDidChange);
    }

    replaceContentView(oldContentView, newContentView)
    {
        console.assert(oldContentView instanceof WebInspector.ContentView);
        if (!(oldContentView instanceof WebInspector.ContentView))
            return;

        console.assert(newContentView instanceof WebInspector.ContentView);
        if (!(newContentView instanceof WebInspector.ContentView))
            return;

        console.assert(oldContentView.parentContainer === this);
        if (oldContentView.parentContainer !== this)
            return;

        console.assert(!newContentView.parentContainer || newContentView.parentContainer === this);
        if (newContentView.parentContainer && newContentView.parentContainer !== this)
            return;

        var currentlyShowing = (this.currentContentView === oldContentView);
        if (currentlyShowing)
            this._hideEntry(this.currentBackForwardEntry);

        // Disassociate with the old content view.
        this._disassociateFromContentView(oldContentView, false);

        // Associate with the new content view.
        newContentView._parentContainer = this;

        // Replace all occurrences of oldContentView with newContentView in the back/forward list.
        for (var i = 0; i < this._backForwardList.length; ++i) {
            if (this._backForwardList[i].contentView === oldContentView) {
                console.assert(!this._backForwardList[i].tombstone);
                let currentCookie = this._backForwardList[i].cookie;
                this._backForwardList[i] = new WebInspector.BackForwardEntry(newContentView, currentCookie);
            }
        }

        // Re-show the current entry, because its content view instance was replaced.
        if (currentlyShowing) {
            this._showEntry(this.currentBackForwardEntry, true);
            this.dispatchEventToListeners(WebInspector.ContentViewContainer.Event.CurrentContentViewDidChange);
        }
    }

    closeAllContentViewsOfPrototype(constructor)
    {
        if (!this._backForwardList.length) {
            console.assert(this._currentIndex === -1);
            return;
        }

        // Do a check to see if all the content views are instances of this prototype.
        // If they all are we can use the quicker closeAllContentViews method.
        var allSamePrototype = true;
        for (var i = this._backForwardList.length - 1; i >= 0; --i) {
            if (!(this._backForwardList[i].contentView instanceof constructor)) {
                allSamePrototype = false;
                break;
            }
        }

        if (allSamePrototype) {
            this.closeAllContentViews();
            return;
        }

        var visibleContentView = this.currentContentView;

        var backForwardListDidChange = false;
        // Hide and disassociate with all the content views that are instances of the constructor.
        for (var i = this._backForwardList.length - 1; i >= 0; --i) {
            var entry = this._backForwardList[i];
            if (!(entry.contentView instanceof constructor))
                continue;

            if (entry.contentView === visibleContentView)
                this._hideEntry(entry);

            if (this._currentIndex >= i) {
                // Decrement the currentIndex since we will remove an item in the back/forward array
                // that it the current index or comes before it.
                --this._currentIndex;
            }

            this._disassociateFromContentView(entry.contentView, entry.tombstone);

            // Remove the item from the back/forward list.
            this._backForwardList.splice(i, 1);
            backForwardListDidChange = true;
        }

        var currentEntry = this.currentBackForwardEntry;
        console.assert(currentEntry || (!currentEntry && this._currentIndex === -1));

        if (currentEntry && currentEntry.contentView !== visibleContentView || backForwardListDidChange) {
            this._showEntry(currentEntry, true);
            this.dispatchEventToListeners(WebInspector.ContentViewContainer.Event.CurrentContentViewDidChange);
        }
    }

    closeContentView(contentViewToClose)
    {
        if (!this._backForwardList.length) {
            console.assert(this._currentIndex === -1);
            return;
        }

        // Do a check to see if all the content views are instances of this prototype.
        // If they all are we can use the quicker closeAllContentViews method.
        var allSameContentView = true;
        for (var i = this._backForwardList.length - 1; i >= 0; --i) {
            if (this._backForwardList[i].contentView !== contentViewToClose) {
                allSameContentView = false;
                break;
            }
        }

        if (allSameContentView) {
            this.closeAllContentViews();
            return;
        }

        var visibleContentView = this.currentContentView;

        var backForwardListDidChange = false;
        // Hide and disassociate with all the content views that are the same as contentViewToClose.
        for (var i = this._backForwardList.length - 1; i >= 0; --i) {
            var entry = this._backForwardList[i];
            if (entry.contentView !== contentViewToClose)
                continue;

            if (entry.contentView === visibleContentView)
                this._hideEntry(entry);

            if (this._currentIndex >= i) {
                // Decrement the currentIndex since we will remove an item in the back/forward array
                // that it the current index or comes before it.
                --this._currentIndex;
            }

            this._disassociateFromContentView(entry.contentView, entry.tombstone);

            // Remove the item from the back/forward list.
            this._backForwardList.splice(i, 1);
            backForwardListDidChange = true;
        }

        var currentEntry = this.currentBackForwardEntry;
        console.assert(currentEntry || (!currentEntry && this._currentIndex === -1));

        if (currentEntry && currentEntry.contentView !== visibleContentView || backForwardListDidChange) {
            this._showEntry(currentEntry, true);
            this.dispatchEventToListeners(WebInspector.ContentViewContainer.Event.CurrentContentViewDidChange);
        }
    }

    closeAllContentViews()
    {
        if (!this._backForwardList.length) {
            console.assert(this._currentIndex === -1);
            return;
        }

        var visibleContentView = this.currentContentView;

        // Hide and disassociate with all the content views.
        for (var i = 0; i < this._backForwardList.length; ++i) {
            var entry = this._backForwardList[i];
            if (entry.contentView === visibleContentView)
                this._hideEntry(entry);
            this._disassociateFromContentView(entry.contentView, entry.tombstone);
        }

        this._backForwardList = [];
        this._currentIndex = -1;

        this.dispatchEventToListeners(WebInspector.ContentViewContainer.Event.CurrentContentViewDidChange);
    }

    canGoBack()
    {
        return this._currentIndex > 0;
    }

    canGoForward()
    {
        return this._currentIndex < this._backForwardList.length - 1;
    }

    goBack()
    {
        if (!this.canGoBack())
            return;
        this.showBackForwardEntryForIndex(this._currentIndex - 1);
    }

    goForward()
    {
        if (!this.canGoForward())
            return;
        this.showBackForwardEntryForIndex(this._currentIndex + 1);
    }

    shown()
    {
        var currentEntry = this.currentBackForwardEntry;
        if (!currentEntry)
            return;

        this._showEntry(currentEntry, true);
    }

    hidden()
    {
        var currentEntry = this.currentBackForwardEntry;
        if (!currentEntry)
            return;

        this._hideEntry(currentEntry);
    }

    // Private

    _takeOwnershipOfContentView(contentView)
    {
        console.assert(contentView.parentContainer !== this, "We already have ownership of the ContentView");
        if (contentView.parentContainer === this)
            return;

        if (contentView.parentContainer)
            contentView.parentContainer._placeTombstonesForContentView(contentView);

        contentView._parentContainer = this;

        this._clearTombstonesForContentView(contentView);
    }

    _placeTombstonesForContentView(contentView)
    {
        console.assert(contentView.parentContainer === this);

        // Ensure another ContentViewContainer doesn't close this ContentView while we still have it.
        let tombstoneContentViewContainers = this._tombstoneContentViewContainersForContentView(contentView);
        console.assert(!tombstoneContentViewContainers.includes(this));

        let visibleContentView = this.currentContentView;

        for (let entry of this._backForwardList) {
            if (entry.contentView !== contentView)
                continue;

            if (entry.contentView === visibleContentView) {
                this._hideEntry(entry);
                visibleContentView = null;
            }

            console.assert(!entry.tombstone);
            entry.tombstone = true;

            tombstoneContentViewContainers.push(this);
        }
    }

    _clearTombstonesForContentView(contentView)
    {
        console.assert(contentView.parentContainer === this);

        let tombstoneContentViewContainers = this._tombstoneContentViewContainersForContentView(contentView);
        const onlyFirst = false;
        tombstoneContentViewContainers.remove(this, onlyFirst);

        for (let entry of this._backForwardList) {
            if (entry.contentView !== contentView)
                continue;

            console.assert(entry.tombstone);
            entry.tombstone = false;
        }
    }

    _disassociateFromContentView(contentView, isTombstone)
    {
        // Just remove one of our tombstone back references.
        // There may be other back/forward entries that need a reference.
        if (isTombstone) {
            let tombstoneContentViewContainers = this._tombstoneContentViewContainersForContentView(contentView);
            const onlyFirst = true;
            tombstoneContentViewContainers.remove(this, onlyFirst);
            return;
        }

        console.assert(!contentView.visible);

        if (!contentView._parentContainer)
            return;

        contentView._parentContainer = null;

        // If another ContentViewContainer has tombstones for this, just transfer
        // ownership to that ContentViewContainer and avoid closing the ContentView.
        // We don't care who we transfer this to, so just use the first.
        let tombstoneContentViewContainers = this._tombstoneContentViewContainersForContentView(contentView);
        if (tombstoneContentViewContainers && tombstoneContentViewContainers.length) {
            tombstoneContentViewContainers[0]._takeOwnershipOfContentView(contentView);
            return;
        }

        contentView.closed();

        if (contentView.representedObject)
            WebInspector.ContentView.closedContentViewForRepresentedObject(contentView.representedObject);
    }

    _showEntry(entry, shouldCallShown)
    {
        console.assert(entry instanceof WebInspector.BackForwardEntry);

        // We may be showing a tombstone from a BackForward list or when re-showing a container
        // that had previously had the content view transferred away from it.
        // Take over the ContentView.
        if (entry.tombstone) {
            this._takeOwnershipOfContentView(entry.contentView);
            console.assert(!entry.tombstone);
        }

        if (!this.subviews.includes(entry.contentView))
            this.addSubview(entry.contentView)

        entry.prepareToShow(shouldCallShown);
    }

    _hideEntry(entry)
    {
        console.assert(entry instanceof WebInspector.BackForwardEntry);

        // If this was a tombstone, the content view should already have been
        // hidden when we placed the tombstone.
        if (entry.tombstone)
            return;

        entry.prepareToHide();
        if (this.subviews.includes(entry.contentView))
            this.removeSubview(entry.contentView)
    }

    _tombstoneContentViewContainersForContentView(contentView)
    {
        let tombstoneContentViewContainers = contentView[WebInspector.ContentViewContainer.TombstoneContentViewContainersSymbol];
        if (!tombstoneContentViewContainers)
            tombstoneContentViewContainers = contentView[WebInspector.ContentViewContainer.TombstoneContentViewContainersSymbol] = [];
        return tombstoneContentViewContainers;
    }
};

WebInspector.ContentViewContainer.Event = {
    CurrentContentViewDidChange: "content-view-container-current-content-view-did-change"
};

WebInspector.ContentViewContainer.TombstoneContentViewContainersSymbol = Symbol("content-view-container-tombstone-content-view-containers");
