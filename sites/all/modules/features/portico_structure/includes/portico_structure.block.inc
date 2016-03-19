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

  $blocks['alerts'] = array(
    'info' => t('Alerts Block'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );

  return $blocks;
}

/**
 * [portico_structure_menu_block_blocks description]
 * @return [type] [description]
 */
function portico_structure_menu_block_blocks() {
  return array(
    // The array key is the block id used by menu block.
    'main-menu' => array(
      // Use the array keys/values described in menu_tree_build().
      'menu_name'   => 'main-menu',
      'parent_mlid' => 0,
      'title_link'  => FALSE,
      'admin_title' => 'Main Menu (Portico Structure)',
      'level'       => 1,
      'follow'      => 0,
      'depth'       => 0,
      'expanded'    => TRUE,
      'sort'        => FALSE,
    ),
  );
}

/**
 * Implements hook_block_view().
 */
function portico_structure_block_view($delta = '') {
  $block = array();

  switch ($delta) {

    case 'hero_image_title':
      if (path_is_admin(current_path())) {
        return FALSE;
      }

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

    case 'alerts':
      $block['subject'] = '';
      $block['content'] = portico_structure_alerts();
      break;

  }

  return $block;
}

/**
 * [portico_structure_alerts description]
 * @return [type] [description]
 */
function portico_structure_alerts() {

  $efq = new EntityFieldQuery();
  $efq->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'alert')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->range(0,1)
      ->propertyOrderBy('created', 'DESC');

  $result = $efq->execute();
  if (empty($result['node'])) {
    return FALSE;
  }

  $result_node = reset($result['node']);
  $node = node_load($result_node->nid);

  $image = field_get_items('node', $node, 'field_image');
  $image = reset($image);

  if (!empty($image)) {

    try {
      $image_url = file_create_url($image['uri']);
    } catch (Exception $e) {}

    $css = '
      #portico-alert {
        background-image: url("' . $image_url . '");
      }
    ';

    drupal_add_css($css, 'inline');
  }

  $text = field_get_items('node', $node, 'body');
  if (!empty($text)) {
    $text = reset($text);

  } else {
    $text = '';
  }

  return array('#markup' => '<div id="portico-alert"><div class="text">' . $text['safe_value'] . '</div></div>');
}

/**
 * [portico_structure_block_view_alter description]
 * @param  [type] &$data [description]
 * @param  [type] $block [description]
 * @return [type]        [description]
 */
function portico_structure_block_view_alter(&$data, $block) {
  if ($block->module == 'menu_block') {
    $data['subject'] = '';
  }
}

/**
 * [portico_structure_apply_bg description]
 * @param  [type] $entity [description]
 * @param  [type] $type   [description]
 * @param  string $field  [description]
 * @return [type]         [description]
 */
function portico_structure_apply_bg($entity, $type, $field = 'field_image') {

  if (drupal_is_front_page()) {

    $markup =
      "<video autoplay loop>
        <source preload='auto' src='" .

        '/sites/default/files/video/hero-video-small.mp4'

        . "' type='video/mp4' />
      </video>";

    return array('#markup' => $markup);

  }

  try {

    $wrapper = entity_metadata_wrapper($type, $entity);

    if (!empty($wrapper->field_subtype)) {
      $subtype = $wrapper->field_subtype->value();
      switch ($subtype) {
        case 'sermons':
            $query = new EntityFieldQuery;
            $query->entityCondition('entity_type', 'node')
                  ->entityCondition('bundle', 'sermon')
                  ->range(0,1)
                  ->propertyCondition('status', NODE_PUBLISHED)
                  ->fieldOrderBy('field_date','value', 'DESC');

            $result = $query->execute();
            if (empty($result['node'])) {
              // return array('#markup' => '');
              return array();
            }

          $sermon = reset($result['node']);
          $return = portico_structure_sermon_promo($sermon->nid);
          return $return;
          break;
      }
    }

    $image = entity_metadata_yank_raw($wrapper, $field);

    $style_name = '1600-500';

    drupal_alter('bg', $style_name, $entity);

    if (!empty($image)) {

      try {

        $derivative_uri = image_style_path($style_name, $image['uri']);
        $style = image_style_load($style_name);
        $success = file_exists($derivative_uri) ||
          image_style_create_derivative($style, $image['uri'], $derivative_uri);
        $image_url = file_create_url($derivative_uri);

      } catch (Exception $e) {}


      $css = '
        body.page-' . drupal_html_class($type) . '-' . $wrapper->getIdentifier() . ' #hero {
          background-image: url("' . $image_url . '");
        }
      ';

      drupal_add_css($css, 'inline');

    }

    if ($type == 'taxonomy_term') {

      $titleImage = field_get_items('taxonomy_term', $entity, 'field_title_image');

      $titleOptions = array(
        'label' => 'hidden',
        'type' => 'image',
      );

      $titleImageRenderable = field_view_value('taxonomy_term', $entity, 'field_title_image', $titleImage[0], $titleOptions);

      return array('#markup' => render($titleImageRenderable));
    }

    return;

  } catch(Exception $e) {

  }
}

function entity_metadata_yank_raw($wrapper, $field) {
  if ($wrapper->__isset($field)) {
    return $wrapper->$field->raw();
  }
  else {
    return FALSE;
  }
}

/**
 * [portico_structure_location description]
 * @return [type] [description]
 */
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
        '#markup' => $location_markup,
      ),
    ),

    'map' => array(
      '#type' => 'container',
      '#attributes' => array('class' => array('map')),
      'location' => array(
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
 * [portico_structure_sermon_promo description]
 * @return [type] [description]
 */
function portico_structure_sermon_promo($nid = NULL) {

  $var = variable_get('portico_config', '');

  // Bail Quick
  if (empty($var['sermon']) && empty($nid)) return FALSE;

  $sermon = empty($nid) ? $var['sermon'] : $nid;
  $sermon = node_load($sermon);

  // Series is a required field.
  $series_tid = $sermon->field_series['und'][0]['tid'];
  $series = taxonomy_term_load($series_tid);

  $sermon_page = portico_structure_get_subtype('sermons');

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

  $selector = empty($nid) ? '#block-portico-structure-sermon-promo' :
    'body.node-type-page #hero';

  $css = $selector . '
     {
      background-image: url("' . $entity_image_url . '");
    }
  ';

  // Add the CSS
  drupal_add_css($css, 'inline');

  $titleImage = field_get_items('taxonomy_term', $series, 'field_title_image');
  $titleOptions = array(
    'label' => 'hidden',
    'type' => 'image',
    'settings' => array(
      'image_link' => 'none',
    ),
  );

  $titleImageRenderable = field_view_value('taxonomy_term', $series, 'field_title_image', $titleImage[0], $titleOptions);

  $return = array(
    'series-area' => array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('left'),
      ),
      'series-info' => $titleImageRenderable,
    ),
    'sermon-area' => array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('right'),
      ),
      'inner' => array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('inner'),
        ),
        'node' => node_view($sermon, 'blog_teaser'),
        'link' => array('#markup' => l('View Series','taxonomy/term/'.$series_tid)),
      ),
    ),
  );

  if (!empty($sermon_page) && empty($nid)) {
    $return['sermon-area']['inner']['link2']['#markup'] =
      l('View All Messages', 'node/' . $sermon_page->nid);
  }

  return $return;
}
