<?php
/**
 * @file
 * portico_resources.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function portico_resources_ctools_plugin_api($module = NULL, $api = NULL) {
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
function portico_resources_node_info() {
  $items = array(
    'resource_page' => array(
      'name' => t('Resource Page'),
      'base' => 'node_content',
      'description' => t('Initiatives like Pray30 or Bible Reading Plans use this content type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
