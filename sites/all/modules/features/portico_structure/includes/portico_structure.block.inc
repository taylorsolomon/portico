<?php

/**
 * Implements hook_block_info().
 */
function portico_structure_block_info() {

  $blocks['hero_image_title'] = array(
    'info' => t('Hero Image / Title'),
    'cache' => DRUPAL_CACHE_PER_PAGE,
  );

  $blocks['location'] = array(
    'info' => t('Location / Times Block'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function portico_structure_block_view($delta = '') {
  $block = array();

  switch ($delta) {

    case 'hero_image_title':
      $entity = menu_get_object();
      $block['subject'] = '';
      $block['content'] = portico_structure_apply_bg($entity);
      break;

    case 'location':
      $block['subject'] = '';
      $block['content'] = portico_structure_location();
      break;

  }

  return $block;
}

function portico_structure_apply_bg($entity, $field = 'field_image') {

  if (drupal_is_front_page()) {

    $markup =
      "<video autoplay loop>
        <source preload='auto' src='" .

        '/sites/default/files/video/coffee.webm'

        . "' type='video/webm' />
      </video>";

    return array('#markup' => $markup);
  }

  $wrapper = entity_metadata_wrapper('node', $entity);

  $image = entity_metadata_yank_raw($wrapper, $field);

  if (empty($image)) {
    $just_show_title = TRUE;
  }

  try {

    $derivative_uri = image_style_path('1600-500', $image['uri']);
    $style = image_style_load('1600-500');
    $success = file_exists($derivative_uri) ||
      image_style_create_derivative($style, $image['uri'], $derivative_uri);
    $image_url = file_create_url($derivative_uri);

  } catch (Exception $e) {

    $just_show_title = TRUE;
  }

  $css = '
    #hero {
      background-image: url("' . $image_url . '");
    }
  ';

  drupal_add_css($css, 'inline');

  return;

}

function entity_metadata_yank_raw($wrapper, $field) {
  if ($wrapper->__isset($field)) {
    return $wrapper->$field->raw();
  }
  else {
    return FALSE;
  }
}


function portico_structure_location() {
  $var = variable_get('portico_config', '');

  $location_markup = $var['address'] . ': ' . $var['service-time'];

  $map_markup = '<div id="map-canvas"></div>';

  $content = array(
    'locaish' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container')),
      'location' => array(
        '#type' => 'markup',
        '#markup' => $location_markup,
      ),
    ),

    'map' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('map')),
      'location' => array(
        '#type' => 'markup',
        '#markup' => $map_markup,
      ),
    ),

  );

  $browser_key = 'AIzaSyCxncqkLAX4lR6I7wb_rAIFNNjZRpuV9Sg';
  drupal_add_js('https://maps.googleapis.com/maps/api/js?key=' . $browser_key, 'external');
  drupal_add_js(array(
    'portico_structure' => array(
      'mapLat' => $var['lat'],
      'mapLng' => $var['long'],
      ),
    ), 'setting'
  );

  // Attach that Google Maps API JS
  $path = drupal_get_path('module', 'portico_structure');
  drupal_add_js($path . '/js/googlemaps.js', 'file');

  return render($content);
}

/**
 * Implementation of hook_preprocess_block().
 */
function portico_structure_preprocess_block(&$variables) {
  // dpm($variables);
}
