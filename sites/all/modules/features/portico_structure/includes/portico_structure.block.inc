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

  $blocks['sermon_promo'] = array(
    'info' => t('Most Recent Sermon'),
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
      $type = 'node';

      if (empty($entity)) {
        $entity = menu_get_item();

        $entity = $entity['map'][($entity['number_parts'] - 1)];
        $type = 'taxonomy_term';
      }

      $block['subject'] = '';
      $block['content'] = portico_structure_apply_bg($entity, $type);
      break;

    case 'location':
      $block['subject'] = '';
      $block['content'] = portico_structure_location();
      break;

    case 'sermon_promo':
      $block['subject'] = '';
      $block['content'] = portico_structure_sermon_promo();
      break;

  }

  return $block;
}

function portico_structure_apply_bg($entity, $type, $field = 'field_image') {

  if (drupal_is_front_page()) {

    $markup =
      "<video autoplay loop>
        <source preload='auto' src='" .

        '/sites/default/files/video/coffee.webm'

        . "' type='video/webm' />
      </video>";

    return array('#markup' => $markup);
  }

  $wrapper = entity_metadata_wrapper($type, $entity);
  $image = entity_metadata_yank_raw($wrapper, $field);

  if (!empty($image)) {

    try {

      $derivative_uri = image_style_path('1600-500', $image['uri']);
      $style = image_style_load('1600-500');
      $success = file_exists($derivative_uri) ||
        image_style_create_derivative($style, $image['uri'], $derivative_uri);
      $image_url = file_create_url($derivative_uri);

    } catch (Exception $e) {


    }

    $css = '
      #hero {
        background-image: url("' . $image_url . '");
      }
    ';

    drupal_add_css($css, 'inline');

  }

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

  $location_markup = '<div class=\'inner\'>
    <span class="heading">Location &amp; Service Time</span>' .
    '<span class=\'address\'>' . $var['address'] . ': ' . $var['service-time'] .
    '</span></div>';

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




function portico_structure_sermon_promo() {

  $var = variable_get('portico_config', '');

  // Bail Quick
  if (empty($var['sermon'])) return FALSE;

  $sermon = node_load($var['sermon']);
  // Series is a required field.
  $series_tid = $sermon->field_series['und'][0]['tid'];
  $series = taxonomy_term_load($series_tid);

  try {
    // Check for parent's image
    $image = $series->field_image['und'][0];
    $derivative_uri = image_style_path('1600-400', $image['uri']);
    $style = image_style_load('1600-400');
    $success = file_exists($derivative_uri) ||
      image_style_create_derivative($style, $image['uri'], $derivative_uri);
    $entity_image_url = file_create_url($derivative_uri);

  } catch (Exception $e) {
    return FALSE;
  }

  $css = '
    #block-portico-structure-sermon-promo {
      background-image: url("' . $entity_image_url . '");
    }
  ';

  // Add the CSS
  drupal_add_css($css, 'inline');

}

