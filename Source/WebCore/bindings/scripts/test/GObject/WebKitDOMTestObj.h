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

#ifndef WebKitDOMTestObj_h
#define WebKitDOMTestObj_h

#include "webkit/webkitdomdefines.h"
#include <glib-object.h>
#include <webkit/webkitdefines.h>
#include "webkit/WebKitDOMObject.h"


G_BEGIN_DECLS
#define WEBKIT_TYPE_DOM_TEST_OBJ            (webkit_dom_test_obj_get_type())
#define WEBKIT_DOM_TEST_OBJ(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), WEBKIT_TYPE_DOM_TEST_OBJ, WebKitDOMTestObj))
#define WEBKIT_DOM_TEST_OBJ_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  WEBKIT_TYPE_DOM_TEST_OBJ, WebKitDOMTestObjClass)
#define WEBKIT_DOM_IS_TEST_OBJ(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), WEBKIT_TYPE_DOM_TEST_OBJ))
#define WEBKIT_DOM_IS_TEST_OBJ_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  WEBKIT_TYPE_DOM_TEST_OBJ))
#define WEBKIT_DOM_TEST_OBJ_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  WEBKIT_TYPE_DOM_TEST_OBJ, WebKitDOMTestObjClass))

struct _WebKitDOMTestObj {
    WebKitDOMObject parent_instance;
};

struct _WebKitDOMTestObjClass {
    WebKitDOMObjectClass parent_class;
};

WEBKIT_API GType
webkit_dom_test_obj_get_type (void);

/**
 * webkit_dom_test_obj_void_method:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_void_method(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_void_method_with_args:
 * @self: A #WebKitDOMTestObj
 * @int_arg: A #glong
 * @str_arg: A #gchar
 * @obj_arg: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_void_method_with_args(WebKitDOMTestObj* self, glong int_arg, const gchar* str_arg, WebKitDOMTestObj* obj_arg);

/**
 * webkit_dom_test_obj_int_method:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_int_method(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_int_method_with_args:
 * @self: A #WebKitDOMTestObj
 * @int_arg: A #glong
 * @str_arg: A #gchar
 * @obj_arg: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_int_method_with_args(WebKitDOMTestObj* self, glong int_arg, const gchar* str_arg, WebKitDOMTestObj* obj_arg);

/**
 * webkit_dom_test_obj_obj_method:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_obj_method(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_obj_method_with_args:
 * @self: A #WebKitDOMTestObj
 * @int_arg: A #glong
 * @str_arg: A #gchar
 * @obj_arg: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_obj_method_with_args(WebKitDOMTestObj* self, glong int_arg, const gchar* str_arg, WebKitDOMTestObj* obj_arg);

/**
 * webkit_dom_test_obj_method_that_requires_all_args_and_throws:
 * @self: A #WebKitDOMTestObj
 * @str_arg: A #gchar
 * @obj_arg: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_method_that_requires_all_args_and_throws(WebKitDOMTestObj* self, const gchar* str_arg, WebKitDOMTestObj* obj_arg, GError **error);

/**
 * webkit_dom_test_obj_serialized_value:
 * @self: A #WebKitDOMTestObj
 * @serialized_arg: A #WebKitDOMSerializedScriptValue
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_serialized_value(WebKitDOMTestObj* self, WebKitDOMSerializedScriptValue* serialized_arg);

/**
 * webkit_dom_test_obj_idb_key:
 * @self: A #WebKitDOMTestObj
 * @key: A #WebKitDOMIDBKey
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_idb_key(WebKitDOMTestObj* self, WebKitDOMIDBKey* key);

/**
 * webkit_dom_test_obj_options_object:
 * @self: A #WebKitDOMTestObj
 * @oo: A #WebKitDOMOptionsObject
 * @ooo: A #WebKitDOMOptionsObject
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_options_object(WebKitDOMTestObj* self, WebKitDOMOptionsObject* oo, WebKitDOMOptionsObject* ooo);

/**
 * webkit_dom_test_obj_method_with_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_with_script_state_void:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_with_script_state_void(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_with_script_state_obj:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_with_script_state_obj(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_with_script_state_void_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_with_script_state_void_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_with_script_state_obj_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_with_script_state_obj_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_with_script_execution_context:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_with_script_execution_context(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_with_script_execution_context_and_script_state:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_with_script_execution_context_and_script_state(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_with_script_execution_context_and_script_state_obj_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_with_script_execution_context_and_script_state_obj_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_with_script_execution_context_and_script_state_with_spaces:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_with_script_execution_context_and_script_state_with_spaces(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_method_with_optional_arg:
 * @self: A #WebKitDOMTestObj
 * @opt: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_optional_arg(WebKitDOMTestObj* self, glong opt);

/**
 * webkit_dom_test_obj_method_with_non_optional_arg_and_optional_arg:
 * @self: A #WebKitDOMTestObj
 * @non_opt: A #glong
 * @opt: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_non_optional_arg_and_optional_arg(WebKitDOMTestObj* self, glong non_opt, glong opt);

/**
 * webkit_dom_test_obj_method_with_non_optional_arg_and_two_optional_args:
 * @self: A #WebKitDOMTestObj
 * @non_opt: A #glong
 * @opt1: A #glong
 * @opt2: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_non_optional_arg_and_two_optional_args(WebKitDOMTestObj* self, glong non_opt, glong opt1, glong opt2);

/**
 * webkit_dom_test_obj_method_with_optional_string:
 * @self: A #WebKitDOMTestObj
 * @str: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_optional_string(WebKitDOMTestObj* self, const gchar* str);

/**
 * webkit_dom_test_obj_method_with_optional_string_is_undefined:
 * @self: A #WebKitDOMTestObj
 * @str: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_optional_string_is_undefined(WebKitDOMTestObj* self, const gchar* str);

/**
 * webkit_dom_test_obj_method_with_optional_string_is_null_string:
 * @self: A #WebKitDOMTestObj
 * @str: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_method_with_optional_string_is_null_string(WebKitDOMTestObj* self, const gchar* str);

/**
 * webkit_dom_test_obj_conditional_method1:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_conditional_method1(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_conditional_method2:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_conditional_method2(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_conditional_method3:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_conditional_method3(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_class_method:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_class_method(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_class_method_with_optional:
 * @self: A #WebKitDOMTestObj
 * @arg: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_class_method_with_optional(WebKitDOMTestObj* self, glong arg);

/**
 * webkit_dom_test_obj_overloaded_method1:
 * @self: A #WebKitDOMTestObj
 * @arg: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_overloaded_method1(WebKitDOMTestObj* self, glong arg);

/**
 * webkit_dom_test_obj_overloaded_method1:
 * @self: A #WebKitDOMTestObj
 * @type: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_overloaded_method1(WebKitDOMTestObj* self, const gchar* type);

/**
 * webkit_dom_test_obj_convert1:
 * @self: A #WebKitDOMTestObj
 * @: A #WebKitDOMa
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_convert1(WebKitDOMTestObj* self, WebKitDOMa* );

/**
 * webkit_dom_test_obj_convert2:
 * @self: A #WebKitDOMTestObj
 * @: A #WebKitDOMb
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_convert2(WebKitDOMTestObj* self, WebKitDOMb* );

/**
 * webkit_dom_test_obj_convert3:
 * @self: A #WebKitDOMTestObj
 * @: A #WebKitDOMc
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_convert3(WebKitDOMTestObj* self, WebKitDOMc* );

/**
 * webkit_dom_test_obj_convert4:
 * @self: A #WebKitDOMTestObj
 * @: A #WebKitDOMd
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_convert4(WebKitDOMTestObj* self, WebKitDOMd* );

/**
 * webkit_dom_test_obj_convert5:
 * @self: A #WebKitDOMTestObj
 * @: A #WebKitDOMe
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_convert5(WebKitDOMTestObj* self, WebKitDOMe* );

/**
 * webkit_dom_test_obj_mutable_point_function:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMSVGPoint*
webkit_dom_test_obj_mutable_point_function(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_immutable_point_function:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMSVGPoint*
webkit_dom_test_obj_immutable_point_function(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_orange:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_orange(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_strict_function:
 * @self: A #WebKitDOMTestObj
 * @str: A #gchar
 * @a: A #gfloat
 * @b: A #gint
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMbool*
webkit_dom_test_obj_strict_function(WebKitDOMTestObj* self, const gchar* str, gfloat a, gint b, GError **error);

/**
 * webkit_dom_test_obj_get_read_only_int_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_read_only_int_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_get_read_only_string_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_read_only_string_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_get_read_only_test_obj_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_read_only_test_obj_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_get_short_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gshort
webkit_dom_test_obj_get_short_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_short_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gshort
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_short_attr(WebKitDOMTestObj* self, gshort value);

/**
 * webkit_dom_test_obj_get_unsigned_short_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gushort
webkit_dom_test_obj_get_unsigned_short_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_unsigned_short_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gushort
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_unsigned_short_attr(WebKitDOMTestObj* self, gushort value);

/**
 * webkit_dom_test_obj_get_int_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_int_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_int_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_int_attr(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_long_long_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gint64
webkit_dom_test_obj_get_long_long_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_long_long_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gint64
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_long_long_attr(WebKitDOMTestObj* self, gint64 value);

/**
 * webkit_dom_test_obj_get_unsigned_long_long_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API guint64
webkit_dom_test_obj_get_unsigned_long_long_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_unsigned_long_long_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #guint64
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_unsigned_long_long_attr(WebKitDOMTestObj* self, guint64 value);

/**
 * webkit_dom_test_obj_get_string_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_string_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_string_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_string_attr(WebKitDOMTestObj* self, const gchar* value);

/**
 * webkit_dom_test_obj_get_test_obj_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_test_obj_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_test_obj_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_test_obj_attr(WebKitDOMTestObj* self, WebKitDOMTestObj* value);

/**
 * webkit_dom_test_obj_get_xml_obj_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_xml_obj_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_xml_obj_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_xml_obj_attr(WebKitDOMTestObj* self, WebKitDOMTestObj* value);

/**
 * webkit_dom_test_obj_get_create:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gboolean
webkit_dom_test_obj_get_create(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_create:
 * @self: A #WebKitDOMTestObj
 * @value: A #gboolean
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_create(WebKitDOMTestObj* self, gboolean value);

/**
 * webkit_dom_test_obj_get_reflected_string_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_reflected_string_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_string_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_string_attr(WebKitDOMTestObj* self, const gchar* value);

/**
 * webkit_dom_test_obj_get_reflected_integral_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_reflected_integral_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_integral_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_integral_attr(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_reflected_unsigned_integral_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gulong
webkit_dom_test_obj_get_reflected_unsigned_integral_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_unsigned_integral_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gulong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_unsigned_integral_attr(WebKitDOMTestObj* self, gulong value);

/**
 * webkit_dom_test_obj_get_reflected_boolean_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gboolean
webkit_dom_test_obj_get_reflected_boolean_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_boolean_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gboolean
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_boolean_attr(WebKitDOMTestObj* self, gboolean value);

/**
 * webkit_dom_test_obj_get_reflected_url_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_reflected_url_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_url_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_url_attr(WebKitDOMTestObj* self, const gchar* value);

/**
 * webkit_dom_test_obj_get_reflected_string_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_reflected_string_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_string_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_string_attr(WebKitDOMTestObj* self, const gchar* value);

/**
 * webkit_dom_test_obj_get_reflected_custom_integral_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_reflected_custom_integral_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_custom_integral_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_custom_integral_attr(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_reflected_custom_boolean_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gboolean
webkit_dom_test_obj_get_reflected_custom_boolean_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_custom_boolean_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gboolean
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_custom_boolean_attr(WebKitDOMTestObj* self, gboolean value);

/**
 * webkit_dom_test_obj_get_reflected_custom_url_attr:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_reflected_custom_url_attr(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_reflected_custom_url_attr:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_reflected_custom_url_attr(WebKitDOMTestObj* self, const gchar* value);

/**
 * webkit_dom_test_obj_get_attr_with_getter_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_attr_with_getter_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_set_attr_with_getter_exception:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_attr_with_getter_exception(WebKitDOMTestObj* self, glong value, GError **error);

/**
 * webkit_dom_test_obj_get_attr_with_setter_exception:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_attr_with_setter_exception(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_attr_with_setter_exception:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_attr_with_setter_exception(WebKitDOMTestObj* self, glong value, GError **error);

/**
 * webkit_dom_test_obj_get_string_attr_with_getter_exception:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_string_attr_with_getter_exception(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_set_string_attr_with_getter_exception:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_string_attr_with_getter_exception(WebKitDOMTestObj* self, const gchar* value, GError **error);

/**
 * webkit_dom_test_obj_get_string_attr_with_setter_exception:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_string_attr_with_setter_exception(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_string_attr_with_setter_exception:
 * @self: A #WebKitDOMTestObj
 * @value: A #gchar
 * @error: #GError
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_string_attr_with_setter_exception(WebKitDOMTestObj* self, const gchar* value, GError **error);

/**
 * webkit_dom_test_obj_get_with_script_state_attribute:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_with_script_state_attribute(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_with_script_state_attribute:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_state_attribute(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_with_script_execution_context_attribute:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_execution_context_attribute(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_with_script_execution_context_attribute:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_execution_context_attribute(WebKitDOMTestObj* self, WebKitDOMTestObj* value);

/**
 * webkit_dom_test_obj_get_with_script_state_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_state_attribute_raises(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_set_with_script_state_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_state_attribute_raises(WebKitDOMTestObj* self, WebKitDOMTestObj* value, GError **error);

/**
 * webkit_dom_test_obj_get_with_script_execution_context_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_execution_context_attribute_raises(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_set_with_script_execution_context_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_execution_context_attribute_raises(WebKitDOMTestObj* self, WebKitDOMTestObj* value, GError **error);

/**
 * webkit_dom_test_obj_get_with_script_execution_context_and_script_state_attribute:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_execution_context_and_script_state_attribute(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_with_script_execution_context_and_script_state_attribute:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_execution_context_and_script_state_attribute(WebKitDOMTestObj* self, WebKitDOMTestObj* value);

/**
 * webkit_dom_test_obj_get_with_script_execution_context_and_script_state_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_execution_context_and_script_state_attribute_raises(WebKitDOMTestObj* self, GError **error);

/**
 * webkit_dom_test_obj_set_with_script_execution_context_and_script_state_attribute_raises:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 * @error: #GError
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_execution_context_and_script_state_attribute_raises(WebKitDOMTestObj* self, WebKitDOMTestObj* value, GError **error);

/**
 * webkit_dom_test_obj_get_with_script_execution_context_and_script_state_with_spaces_attribute:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMTestObj*
webkit_dom_test_obj_get_with_script_execution_context_and_script_state_with_spaces_attribute(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_with_script_execution_context_and_script_state_with_spaces_attribute:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_with_script_execution_context_and_script_state_with_spaces_attribute(WebKitDOMTestObj* self, WebKitDOMTestObj* value);

/**
 * webkit_dom_test_obj_get_conditional_attr1:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_conditional_attr1(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_conditional_attr1:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_conditional_attr1(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_conditional_attr2:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_conditional_attr2(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_conditional_attr2:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_conditional_attr2(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_conditional_attr3:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_conditional_attr3(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_conditional_attr3:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_conditional_attr3(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_content_document:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMDocument*
webkit_dom_test_obj_get_content_document(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_get_mutable_point:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMSVGPoint*
webkit_dom_test_obj_get_mutable_point(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_mutable_point:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMSVGPoint
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_mutable_point(WebKitDOMTestObj* self, WebKitDOMSVGPoint* value);

/**
 * webkit_dom_test_obj_get_immutable_point:
 * @self: A #WebKitDOMTestObj
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API WebKitDOMSVGPoint*
webkit_dom_test_obj_get_immutable_point(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_immutable_point:
 * @self: A #WebKitDOMTestObj
 * @value: A #WebKitDOMSVGPoint
 *
 * Returns: (transfer none):
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_immutable_point(WebKitDOMTestObj* self, WebKitDOMSVGPoint* value);

/**
 * webkit_dom_test_obj_get_strict_float:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gfloat
webkit_dom_test_obj_get_strict_float(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_strict_float:
 * @self: A #WebKitDOMTestObj
 * @value: A #gfloat
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_strict_float(WebKitDOMTestObj* self, gfloat value);

/**
 * webkit_dom_test_obj_get_description:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_description(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_get_id:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API glong
webkit_dom_test_obj_get_id(WebKitDOMTestObj* self);

/**
 * webkit_dom_test_obj_set_id:
 * @self: A #WebKitDOMTestObj
 * @value: A #glong
 *
 * Returns:
 *
**/
WEBKIT_API void
webkit_dom_test_obj_set_id(WebKitDOMTestObj* self, glong value);

/**
 * webkit_dom_test_obj_get_hash:
 * @self: A #WebKitDOMTestObj
 *
 * Returns:
 *
**/
WEBKIT_API gchar*
webkit_dom_test_obj_get_hash(WebKitDOMTestObj* self);

G_END_DECLS

#endif /* WebKitDOMTestObj_h */
