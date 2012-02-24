/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestCustomNamedGetter.h"

#include "ExceptionCode.h"
#include "JSDOMBinding.h"
#include "TestCustomNamedGetter.h"
#include "wtf/text/AtomicString.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTestCustomNamedGetter);
/* Hash table */

static const HashTableValue JSTestCustomNamedGetterTableValues[] =
{
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestCustomNamedGetterConstructor), (intptr_t)0, NoIntrinsic },
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestCustomNamedGetterTable = { 2, 1, JSTestCustomNamedGetterTableValues, 0 };
/* Hash table for constructor */

static const HashTableValue JSTestCustomNamedGetterConstructorTableValues[] =
{
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestCustomNamedGetterConstructorTable = { 1, 0, JSTestCustomNamedGetterConstructorTableValues, 0 };
const ClassInfo JSTestCustomNamedGetterConstructor::s_info = { "TestCustomNamedGetterConstructor", &Base::s_info, &JSTestCustomNamedGetterConstructorTable, 0, CREATE_METHOD_TABLE(JSTestCustomNamedGetterConstructor) };

JSTestCustomNamedGetterConstructor::JSTestCustomNamedGetterConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestCustomNamedGetterConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->globalData());
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSTestCustomNamedGetterPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSTestCustomNamedGetterConstructor::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSTestCustomNamedGetterConstructor, JSDOMWrapper>(exec, &JSTestCustomNamedGetterConstructorTable, static_cast<JSTestCustomNamedGetterConstructor*>(cell), propertyName, slot);
}

bool JSTestCustomNamedGetterConstructor::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSTestCustomNamedGetterConstructor, JSDOMWrapper>(exec, &JSTestCustomNamedGetterConstructorTable, static_cast<JSTestCustomNamedGetterConstructor*>(object), propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSTestCustomNamedGetterPrototypeTableValues[] =
{
    { "anotherFunction", DontDelete | JSC::Function, (intptr_t)static_cast<NativeFunction>(jsTestCustomNamedGetterPrototypeFunctionAnotherFunction), (intptr_t)1, NoIntrinsic },
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestCustomNamedGetterPrototypeTable = { 2, 1, JSTestCustomNamedGetterPrototypeTableValues, 0 };
const ClassInfo JSTestCustomNamedGetterPrototype::s_info = { "TestCustomNamedGetterPrototype", &Base::s_info, &JSTestCustomNamedGetterPrototypeTable, 0, CREATE_METHOD_TABLE(JSTestCustomNamedGetterPrototype) };

JSObject* JSTestCustomNamedGetterPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestCustomNamedGetter>(exec, globalObject);
}

bool JSTestCustomNamedGetterPrototype::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    JSTestCustomNamedGetterPrototype* thisObject = jsCast<JSTestCustomNamedGetterPrototype*>(cell);
    return getStaticFunctionSlot<JSObject>(exec, &JSTestCustomNamedGetterPrototypeTable, thisObject, propertyName, slot);
}

bool JSTestCustomNamedGetterPrototype::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    JSTestCustomNamedGetterPrototype* thisObject = jsCast<JSTestCustomNamedGetterPrototype*>(object);
    return getStaticFunctionDescriptor<JSObject>(exec, &JSTestCustomNamedGetterPrototypeTable, thisObject, propertyName, descriptor);
}

const ClassInfo JSTestCustomNamedGetter::s_info = { "TestCustomNamedGetter", &Base::s_info, &JSTestCustomNamedGetterTable, 0 , CREATE_METHOD_TABLE(JSTestCustomNamedGetter) };

JSTestCustomNamedGetter::JSTestCustomNamedGetter(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestCustomNamedGetter> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

void JSTestCustomNamedGetter::finishCreation(JSGlobalData& globalData)
{
    Base::finishCreation(globalData);
    ASSERT(inherits(&s_info));
}

JSObject* JSTestCustomNamedGetter::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestCustomNamedGetterPrototype::create(exec->globalData(), globalObject, JSTestCustomNamedGetterPrototype::createStructure(globalObject->globalData(), globalObject, globalObject->objectPrototype()));
}

void JSTestCustomNamedGetter::destroy(JSC::JSCell* cell)
{
    JSTestCustomNamedGetter* thisObject = jsCast<JSTestCustomNamedGetter*>(cell);
    thisObject->JSTestCustomNamedGetter::~JSTestCustomNamedGetter();
}

JSTestCustomNamedGetter::~JSTestCustomNamedGetter()
{
    releaseImplIfNotNull();
}

bool JSTestCustomNamedGetter::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    JSTestCustomNamedGetter* thisObject = jsCast<JSTestCustomNamedGetter*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    if (canGetItemsForName(exec, static_cast<TestCustomNamedGetter*>(thisObject->impl()), propertyName)) {
        slot.setCustom(thisObject, thisObject->nameGetter);
        return true;
    }
    return getStaticValueSlot<JSTestCustomNamedGetter, Base>(exec, &JSTestCustomNamedGetterTable, thisObject, propertyName, slot);
}

bool JSTestCustomNamedGetter::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    JSTestCustomNamedGetter* thisObject = jsCast<JSTestCustomNamedGetter*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    if (canGetItemsForName(exec, static_cast<TestCustomNamedGetter*>(thisObject->impl()), propertyName)) {
        PropertySlot slot;
        slot.setCustom(thisObject, nameGetter);
        descriptor.setDescriptor(slot.getValue(exec, propertyName), ReadOnly | DontDelete | DontEnum);
        return true;
    }
    return getStaticValueDescriptor<JSTestCustomNamedGetter, Base>(exec, &JSTestCustomNamedGetterTable, thisObject, propertyName, descriptor);
}

JSValue jsTestCustomNamedGetterConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestCustomNamedGetter* domObject = static_cast<JSTestCustomNamedGetter*>(asObject(slotBase));
    return JSTestCustomNamedGetter::getConstructor(exec, domObject->globalObject());
}

JSValue JSTestCustomNamedGetter::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestCustomNamedGetterConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL jsTestCustomNamedGetterPrototypeFunctionAnotherFunction(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTestCustomNamedGetter::s_info))
        return throwVMTypeError(exec);
    JSTestCustomNamedGetter* castedThis = static_cast<JSTestCustomNamedGetter*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSTestCustomNamedGetter::s_info);
    TestCustomNamedGetter* impl = static_cast<TestCustomNamedGetter*>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createTypeError(exec, "Not enough arguments"));
    const String& str(ustringToString(MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).isEmpty() ? UString() : MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).toString(exec)->value(exec)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    impl->anotherFunction(str);
    return JSValue::encode(jsUndefined());
}

static inline bool isObservable(JSTestCustomNamedGetter* jsTestCustomNamedGetter)
{
    if (jsTestCustomNamedGetter->hasCustomProperties())
        return true;
    return false;
}

bool JSTestCustomNamedGetterOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestCustomNamedGetter* jsTestCustomNamedGetter = static_cast<JSTestCustomNamedGetter*>(handle.get().asCell());
    if (!isObservable(jsTestCustomNamedGetter))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestCustomNamedGetterOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestCustomNamedGetter* jsTestCustomNamedGetter = static_cast<JSTestCustomNamedGetter*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestCustomNamedGetter->impl(), jsTestCustomNamedGetter);
    jsTestCustomNamedGetter->releaseImpl();
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TestCustomNamedGetter* impl)
{
    return wrap<JSTestCustomNamedGetter>(exec, globalObject, impl);
}

TestCustomNamedGetter* toTestCustomNamedGetter(JSC::JSValue value)
{
    return value.inherits(&JSTestCustomNamedGetter::s_info) ? static_cast<JSTestCustomNamedGetter*>(asObject(value))->impl() : 0;
}

}
