/*
 * Copyright (C) 2016 Ole André Vadla Ravnås <oleavr@nowsecure.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#include "apiresolver-fixture.c"

TEST_LIST_BEGIN (api_resolver)
  API_RESOLVER_TESTENTRY (objc)
TEST_LIST_END ()

API_RESOLVER_TESTCASE (objc)
{
  TestForEachContext ctx;
  const gchar * globs[] = { "+[NSAr* arr*]", "-[NSAr* objectAt*]", NULL };

  fixture->resolver = gum_api_resolver_make ("objc");
  if (fixture->resolver == NULL)
  {
    g_print ("<skipping, not available> ");
    return;
  }

  ctx.number_of_calls = 0;
  ctx.value_to_return = TRUE;
  gum_api_resolver_enumerate_matches (fixture->resolver, globs, match_found_cb,
      &ctx);
  g_assert_cmpuint (ctx.number_of_calls, >, 1);

  ctx.number_of_calls = 0;
  ctx.value_to_return = FALSE;
  gum_api_resolver_enumerate_matches (fixture->resolver, globs, match_found_cb,
      &ctx);
  g_assert_cmpuint (ctx.number_of_calls, ==, 1);
}

static gboolean
match_found_cb (const GumApiDetails * details,
                gpointer user_data)
{
  TestForEachContext * ctx = (TestForEachContext *) user_data;

  ctx->number_of_calls++;

  return ctx->value_to_return;
}
