<?php

function splogin_default_rules_configuration() {

  $site_frontpage = variable_get('site_frontpage', 'node');
  $rule = '{ "splogin_redirect_anonymous_user" : {
    "LABEL" : "Redirect anonymous user",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : true,
    "OWNER" : "rules",
    "REQUIRES" : [ "rules" ],
    "ON" : { "init" : [] },
    "IF" : [
      { "text_matches" : { "text" : [ "site:current-page:path" ], "match" : "'.$site_frontpage.'" } },
      { "user_has_role" : {
          "account" : [ "site:current-user" ],
          "roles" : { "value" : { "1" : "1" } }
        }
      }
    ],
    "DO" : [ { "redirect" : { "url" : "login" } } ]
  }
}';

  $configs['splogin_redirect_anonymous_user'] = rules_import($rule);

  return $configs;
}

