<?php

function portico_preprocess_html(&$vars) {
  if (!empty($vars['page']['content']['system_main']['nodes'])) {
    $node = reset($vars['page']['content']['system_main']['nodes']);
    if (!empty($node['#node']->field_subtype['und'][0]['value'])) {
      $vars['classes_array'][] = 'subtype-' . $node['#node']->field_subtype['und'][0]['value'];
    }
  }
}
