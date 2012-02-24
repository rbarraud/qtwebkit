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

#if ENABLE(Condition1) || ENABLE(Condition2)

#include "JSTestInterface.h"

#include "ExceptionCode.h"
#include "JSDOMBinding.h"
#include "JSTestInterfaceCustom.h"
#include "JSTestObj.h"
#include "TestInterface.h"
#include "TestObj.h"
#include "TestSupplemental.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

#if ENABLE(Condition11) || ENABLE(Condition12)
#include "JSNode.h"
#include "KURL.h"
#include <runtime/JSString.h>
#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
#include "Node.h"
#endif

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTestInterface);
/* Hash table */

static const HashTableValue JSTestInterfaceTableValues[] =
{
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr1", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr1), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr2", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr2), (intptr_t)setJSTestInterfaceSupplementalStr2, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalStr3", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalStr3), (intptr_t)setJSTestInterfaceSupplementalStr3, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalNode", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSupplementalNode), (intptr_t)setJSTestInterfaceSupplementalNode, NoIntrinsic },
#endif
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceConstructor), (intptr_t)0, NoIntrinsic },
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestInterfaceTable = { 16, 15, JSTestInterfaceTableValues, 0 };
/* Hash table for constructor */

static const HashTableValue JSTestInterfaceConstructorTableValues[] =
{
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT1", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT1), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT2", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT2), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod4", DontDelete | JSC::Function, (intptr_t)static_cast<NativeFunction>(jsTestInterfaceConstructorFunctionSupplementalMethod4), (intptr_t)0, NoIntrinsic },
#endif
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestInterfaceConstructorTable = { 4, 3, JSTestInterfaceConstructorTableValues, 0 };

#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(1 == TestSupplemental::SUPPLEMENTALCONSTANT1, TestInterfaceEnumSUPPLEMENTALCONSTANT1IsWrongUseDoNotCheckConstants);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(2 == TestSupplemental::CONST_IMPL, TestInterfaceEnumCONST_IMPLIsWrongUseDoNotCheckConstants);
#endif

const ClassInfo JSTestInterfaceConstructor::s_info = { "TestInterfaceConstructor", &Base::s_info, &JSTestInterfaceConstructorTable, 0, CREATE_METHOD_TABLE(JSTestInterfaceConstructor) };

JSTestInterfaceConstructor::JSTestInterfaceConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestInterfaceConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->globalData());
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSTestInterfacePrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->globalData(), exec->propertyNames().length, jsNumber(2), ReadOnly | DontDelete | DontEnum);
}

bool JSTestInterfaceConstructor::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSTestInterfaceConstructor, JSDOMWrapper>(exec, &JSTestInterfaceConstructorTable, static_cast<JSTestInterfaceConstructor*>(cell), propertyName, slot);
}

bool JSTestInterfaceConstructor::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSTestInterfaceConstructor, JSDOMWrapper>(exec, &JSTestInterfaceConstructorTable, static_cast<JSTestInterfaceConstructor*>(object), propertyName, descriptor);
}

EncodedJSValue JSC_HOST_CALL JSTestInterfaceConstructor::constructJSTestInterface(ExecState* exec)
{
    JSTestInterfaceConstructor* jsConstructor = static_cast<JSTestInterfaceConstructor*>(exec->callee());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createTypeError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    const String& str1(ustringToString(MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).isEmpty() ? UString() : MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).toString(exec)->value(exec)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    const String& str2(ustringToString(MAYBE_MISSING_PARAMETER(exec, 1, DefaultIsUndefined).isEmpty() ? UString() : MAYBE_MISSING_PARAMETER(exec, 1, DefaultIsUndefined).toString(exec)->value(exec)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    ScriptExecutionContext* context = jsConstructor->scriptExecutionContext();
    if (!context)
        return throwVMError(exec, createReferenceError(exec, "TestInterface constructor associated document is unavailable"));
    RefPtr<TestInterface> object = TestInterface::create(context, str1, str2, ec);
    if (ec) {
        setDOMException(exec, ec);
        return JSValue::encode(JSValue());
    }
    return JSValue::encode(asObject(toJS(exec, jsConstructor->globalObject(), object.get())));
}

ConstructType JSTestInterfaceConstructor::getConstructData(JSCell*, ConstructData& constructData)
{
    constructData.native.function = constructJSTestInterface;
    return ConstructTypeHost;
}

/* Hash table for prototype */

static const HashTableValue JSTestInterfacePrototypeTableValues[] =
{
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT1", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT1), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "SUPPLEMENTALCONSTANT2", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestInterfaceSUPPLEMENTALCONSTANT2), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod1", DontDelete | JSC::Function, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod1), (intptr_t)0, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod2", DontDelete | JSC::Function, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod2), (intptr_t)2, NoIntrinsic },
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    { "supplementalMethod3", DontDelete | JSC::Function, (intptr_t)static_cast<NativeFunction>(jsTestInterfacePrototypeFunctionSupplementalMethod3), (intptr_t)0, NoIntrinsic },
#endif
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestInterfacePrototypeTable = { 17, 15, JSTestInterfacePrototypeTableValues, 0 };
const ClassInfo JSTestInterfacePrototype::s_info = { "TestInterfacePrototype", &Base::s_info, &JSTestInterfacePrototypeTable, 0, CREATE_METHOD_TABLE(JSTestInterfacePrototype) };

JSObject* JSTestInterfacePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestInterface>(exec, globalObject);
}

bool JSTestInterfacePrototype::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    JSTestInterfacePrototype* thisObject = jsCast<JSTestInterfacePrototype*>(cell);
    return getStaticPropertySlot<JSTestInterfacePrototype, JSObject>(exec, &JSTestInterfacePrototypeTable, thisObject, propertyName, slot);
}

bool JSTestInterfacePrototype::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    JSTestInterfacePrototype* thisObject = jsCast<JSTestInterfacePrototype*>(object);
    return getStaticPropertyDescriptor<JSTestInterfacePrototype, JSObject>(exec, &JSTestInterfacePrototypeTable, thisObject, propertyName, descriptor);
}

const ClassInfo JSTestInterface::s_info = { "TestInterface", &Base::s_info, &JSTestInterfaceTable, 0 , CREATE_METHOD_TABLE(JSTestInterface) };

JSTestInterface::JSTestInterface(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestInterface> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

void JSTestInterface::finishCreation(JSGlobalData& globalData)
{
    Base::finishCreation(globalData);
    ASSERT(inherits(&s_info));
}

JSObject* JSTestInterface::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestInterfacePrototype::create(exec->globalData(), globalObject, JSTestInterfacePrototype::createStructure(globalObject->globalData(), globalObject, globalObject->objectPrototype()));
}

void JSTestInterface::destroy(JSC::JSCell* cell)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(cell);
    thisObject->JSTestInterface::~JSTestInterface();
}

JSTestInterface::~JSTestInterface()
{
    releaseImplIfNotNull();
}

bool JSTestInterface::getOwnPropertySlot(JSCell* cell, ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    return getStaticValueSlot<JSTestInterface, Base>(exec, &JSTestInterfaceTable, thisObject, propertyName, slot);
}

bool JSTestInterface::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    return getStaticValueDescriptor<JSTestInterface, Base>(exec, &JSTestInterfaceTable, thisObject, propertyName, descriptor);
}

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr1(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsString(exec, TestSupplemental::supplementalStr1(impl));
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr2(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = jsString(exec, TestSupplemental::supplementalStr2(impl));
    return result;
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalStr3(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(slotBase));
    return castedThis->supplementalStr3(exec);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSupplementalNode(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(TestSupplemental::supplementalNode(impl)));
    return result;
}

#endif

JSValue jsTestInterfaceConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSTestInterface* domObject = static_cast<JSTestInterface*>(asObject(slotBase));
    return JSTestInterface::getConstructor(exec, domObject->globalObject());
}

void JSTestInterface::put(JSCell* cell, ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    JSTestInterface* thisObject = jsCast<JSTestInterface*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    if (thisObject->putDelegate(exec, propertyName, value, slot))
        return;
    lookupPut<JSTestInterface, Base>(exec, propertyName, value, &JSTestInterfaceTable, thisObject, slot);
}

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalStr2(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    TestSupplemental::setSupplementalStr2(impl, ustringToString(value.isEmpty() ? UString() : value.toString(exec)->value(exec)));
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalStr3(ExecState* exec, JSObject* thisObject, JSValue value)
{
    static_cast<JSTestInterface*>(thisObject)->setSupplementalStr3(exec, value);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
void setJSTestInterfaceSupplementalNode(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(thisObject);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    TestSupplemental::setSupplementalNode(impl, toNode(value));
}

#endif

JSValue JSTestInterface::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestInterfaceConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod1(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTestInterface::s_info))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSTestInterface::s_info);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    TestSupplemental::supplementalMethod1(impl);
    return JSValue::encode(jsUndefined());
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod2(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTestInterface::s_info))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSTestInterface::s_info);
    TestInterface* impl = static_cast<TestInterface*>(castedThis->impl());
    if (exec->argumentCount() < 2)
        return throwVMError(exec, createTypeError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    ScriptExecutionContext* scriptContext = static_cast<JSDOMGlobalObject*>(exec->lexicalGlobalObject())->scriptExecutionContext();
    if (!scriptContext)
        return JSValue::encode(jsUndefined());
    const String& strArg(ustringToString(MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).isEmpty() ? UString() : MAYBE_MISSING_PARAMETER(exec, 0, DefaultIsUndefined).toString(exec)->value(exec)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    TestObj* objArg(toTestObj(MAYBE_MISSING_PARAMETER(exec, 1, DefaultIsUndefined)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());

    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(TestSupplemental::supplementalMethod2(impl, scriptContext, strArg, objArg, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfacePrototypeFunctionSupplementalMethod3(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSTestInterface::s_info))
        return throwVMTypeError(exec);
    JSTestInterface* castedThis = static_cast<JSTestInterface*>(asObject(thisValue));
    ASSERT_GC_OBJECT_INHERITS(castedThis, &JSTestInterface::s_info);
    return JSValue::encode(castedThis->supplementalMethod3(exec));
}

#endif

#if ENABLE(Condition11) || ENABLE(Condition12)
EncodedJSValue JSC_HOST_CALL jsTestInterfaceConstructorFunctionSupplementalMethod4(ExecState* exec)
{
    TestSupplemental::supplementalMethod4();
    return JSValue::encode(jsUndefined());
}

#endif

// Constant getters

#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSUPPLEMENTALCONSTANT1(ExecState* exec, JSValue, const Identifier&)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(1));
}

#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
JSValue jsTestInterfaceSUPPLEMENTALCONSTANT2(ExecState* exec, JSValue, const Identifier&)
{
    UNUSED_PARAM(exec);
    return jsNumber(static_cast<int>(2));
}

#endif
static inline bool isObservable(JSTestInterface* jsTestInterface)
{
    if (jsTestInterface->hasCustomProperties())
        return true;
    return false;
}

bool JSTestInterfaceOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestInterface* jsTestInterface = static_cast<JSTestInterface*>(handle.get().asCell());
    if (jsTestInterface->impl()->hasPendingActivity())
        return true;
    if (!isObservable(jsTestInterface))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestInterfaceOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestInterface* jsTestInterface = static_cast<JSTestInterface*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestInterface->impl(), jsTestInterface);
    jsTestInterface->releaseImpl();
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TestInterface* impl)
{
    return wrap<JSTestInterface>(exec, globalObject, impl);
}

TestInterface* toTestInterface(JSC::JSValue value)
{
    return value.inherits(&JSTestInterface::s_info) ? static_cast<JSTestInterface*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(Condition1) || ENABLE(Condition2)
