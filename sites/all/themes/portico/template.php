<?php

function portico_preprocess_html(&$vars) {
  if (!empty($vars['page']['content']['system_main']['nodes'])) {
    $node = reset($vars['page']['content']['system_main']['nodes']);
    if (!empty($node['#node']->field_subtype['und'][0]['value'])) {
      $vars['classes_array'][] = 'subtype-' . $node['#node']->field_subtype['und'][0]['value'];
    }
  }
}

/**
 * [portico_css_alter description]
 * @param  [type] $css [description]
 * @return [type]      [description]
 */
function portico_css_alter(&$css) {
  // Get the path to the module
  $path = drupal_get_path('module', 'jplayer');

  // Remove the unneeded files from the css array
  unset($css[$path . '/theme/jplayer.css']);
}
