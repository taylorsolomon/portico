<?php
/**
 * @file
 * portico_structure.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function portico_structure_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function portico_structure_image_default_styles() {
  $styles = array();

  // Exported image style: 1024-512.
  $styles['1024-512'] = array(
    'label' => '1024-512',
    'effects' => array(
      2 => array(
        'name' => 'focal_point_scale_and_crop',
        'data' => array(
          'width' => 1024,
          'height' => 512,
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

  // Exported image style: 1200-628.
  $styles['1200-628'] = array(
    'label' => '1200-628',
    'effects' => array(
      1 => array(
        'name' => 'focal_point_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 628,
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

  // Exported image style: 1600-350.
  $styles['1600-350'] = array(
    'label' => '1600-350',
    'effects' => array(
      2 => array(
        'name' => 'focal_point_scale_and_crop',
        'data' => array(
          'width' => 1600,
          'height' => 350,
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

  // Exported image style: 200-300.
  $styles['200-300'] = array(
    'label' => '200-300',
    'effects' => array(
      3 => array(
        'name' => 'focal_point_scale_and_crop',
        'data' => array(
          'width' => 200,
          'height' => 300,
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
    'alert' => array(
      'name' => t('Alert'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'landing' => array(
      'name' => t('Landing'),
      'base' => 'node_content',
      'description' => t('Landing pages and standard pages aren\'t really that different, but landing pages have the ability to set up grids and sidebars, full-width images, etc.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('Standard Page type. Use this one for any content that needs only one text area and possibly an image. If you\'re creating a "subtype" page, use this type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('Persons show up on the leadership page.'),
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
    'content_reference' => array(
      'name' => 'Content Reference',
      'bundle' => 'content_reference',
      'locked' => '1',
    ),
    'full_width_image' => array(
      'name' => 'Full Width Image',
      'bundle' => 'full_width_image',
      'locked' => '1',
    ),
    'grid' => array(
      'name' => 'Grid',
      'bundle' => 'grid',
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
    'spotify_playlist' => array(
      'name' => 'Spotify Playlist',
      'bundle' => 'spotify_playlist',
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
    'the_city' => array(
      'name' => 'The City',
      'bundle' => 'the_city',
      'locked' => '1',
    ),
    'video' => array(
      'name' => 'Video',
      'bundle' => 'video',
      'locked' => '1',
    ),
  );
  return $items;
}
