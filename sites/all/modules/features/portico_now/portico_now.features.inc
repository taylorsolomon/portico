<?php
/**
 * @file
 * portico_now.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function portico_now_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function portico_now_node_info() {
  $items = array(
    'portico_now' => array(
      'name' => t('Portico Now'),
      'base' => 'node_content',
      'description' => t('Portico Now Updates. These show up on the page that is setup with subtype set to "Portico Now Landing Page"'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
