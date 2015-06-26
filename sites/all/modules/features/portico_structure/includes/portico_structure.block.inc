<?php

/**
 * Implements hook_block_info().
 */
function portico_structure_block_info() {

  $blocks['hero_image_title'] = array(
    'info' => t('Hero Image / Title'),
    'cache' => DRUPAL_CACHE_PER_PAGE
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

  }
  return $block;
}

function portico_structure_apply_bg($entity, $field = 'field_image') {

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
