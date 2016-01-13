<?php
/**
 * @file
 * portico_wufoo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function portico_wufoo_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function portico_wufoo_node_info() {
  $items = array(
    'wufoo' => array(
      'name' => t('Wufoo'),
      'base' => 'node_content',
      'description' => t('For wufoo forms. Any new wufoo form will need to be added as a subtype.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
