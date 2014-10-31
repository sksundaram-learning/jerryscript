/* Copyright 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ecma-alloc.h"
#include "ecma-builtins.h"
#include "ecma-conversion.h"
#include "ecma-exceptions.h"
#include "ecma-gc.h"
#include "ecma-globals.h"
#include "ecma-helpers.h"
#include "ecma-objects.h"
#include "ecma-try-catch-macro.h"
#include "globals.h"

#ifndef CONFIG_ECMA_COMPACT_PROFILE_DISABLE_ERROR_BUILTINS

#define ECMA_BUILTINS_INTERNAL
#include "ecma-builtins-internal.h"

#define BUILTIN_INC_HEADER_NAME "ecma-builtin-evalerror.inc.h"
#define BUILTIN_UNDERSCORED_ID eval_error
#include "ecma-builtin-internal-routines-template.inc.h"

/** \addtogroup ecma ECMA
 * @{
 *
 * \addtogroup ecmabuiltins
 * @{
 *
 * \addtogroup evalerror ECMA EvalError object built-in
 * @{
 */

/**
 * Handle calling [[Call]] of built-in EvalError object
 *
 * @return completion-value
 */
ecma_completion_value_t
ecma_builtin_eval_error_dispatch_call (ecma_value_t *arguments_list_p, /**< arguments list */
                                       ecma_length_t arguments_list_len) /**< number of arguments */
{
  JERRY_ASSERT (arguments_list_len == 0 || arguments_list_p != NULL);

  if (arguments_list_len != 0
      && !ecma_is_value_undefined (arguments_list_p [0]))
  {
    ecma_completion_value_t ret_value;

    ECMA_TRY_CATCH (msg_to_str_completion,
                    ecma_op_to_string (arguments_list_p[0]),
                    ret_value);

    ecma_string_t *message_string_p = ECMA_GET_POINTER (msg_to_str_completion.u.value.value);
    ecma_object_t *new_error_object_p = ecma_new_standard_error_with_message (ECMA_ERROR_EVAL,
                                                                              message_string_p);
    ret_value = ecma_make_normal_completion_value (ecma_make_object_value (new_error_object_p));

    ECMA_FINALIZE (msg_to_str_completion);

    return ret_value;
  }
  else
  {
    ecma_object_t *new_error_object_p = ecma_new_standard_error (ECMA_ERROR_EVAL);

    return ecma_make_normal_completion_value (ecma_make_object_value (new_error_object_p));
  }
} /* ecma_builtin_eval_error_dispatch_call */

/**
 * Handle calling [[Construct]] of built-in EvalError object
 *
 * @return completion-value
 */
ecma_completion_value_t
ecma_builtin_eval_error_dispatch_construct (ecma_value_t *arguments_list_p, /**< arguments list */
                                            ecma_length_t arguments_list_len) /**< number of arguments */
{
  return ecma_builtin_eval_error_dispatch_call (arguments_list_p, arguments_list_len);
} /* ecma_builtin_eval_error_dispatch_construct */

/**
 * @}
 * @}
 * @}
 */

#endif /* !CONFIG_ECMA_COMPACT_PROFILE_DISABLE_ERROR_BUILTINS */
