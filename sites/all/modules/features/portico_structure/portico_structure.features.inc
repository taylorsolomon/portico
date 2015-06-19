<?php
/**
 * @file
 * portico_structure.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function portico_structure_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function portico_structure_image_default_styles() {
  $styles = array();

  // Exported image style: 1600-500.
  $styles['1600-500'] = array(
    'label' => '1600-500',
    'effects' => array(
      2 => array(
        'name' => 'focal_point_scale_and_crop',
        'data' => array(
          'width' => 1600,
          'height' => 500,
          'focal_point_advanced' => array(
            'shift_x' => '',
            'shift_y' => '',
          ),
          '#imageinfo_cache_effect_callback' => 'focal_point_scale_and_crop_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function portico_structure_node_info() {
  $items = array(
    'landing' => array(
      'name' => t('Landing'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'sermon' => array(
      'name' => t('Sermon'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function portico_structure_paragraphs_info() {
  $items = array(
    'full_width_image' => array(
      'name' => 'Full Width Image',
      'bundle' => 'full_width_image',
      'locked' => '1',
    ),
    'sidebar_list' => array(
      'name' => 'Sidebar List',
      'bundle' => 'sidebar_list',
      'locked' => '1',
    ),
    'sidebar_text' => array(
      'name' => 'Sidebar Text',
      'bundle' => 'sidebar_text',
      'locked' => '1',
    ),
    'text' => array(
      'name' => 'Text',
      'bundle' => 'text',
      'locked' => '1',
    ),
    'text_and_sidebar' => array(
      'name' => 'Text and Sidebar',
      'bundle' => 'text_and_sidebar',
      'locked' => '1',
    ),
  );
  return $items;
}
