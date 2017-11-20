<?php

/**
 * [portico_config description]
 * @param  [type] $form        [description]
 * @param  [type] &$form_state [description]
 * @return [type]              [description]
 */
function portico_config($form, &$form_state) {
  $var = variable_get('portico_config', '');

  $form['group'] = array(
    '#type' => 'vertical_tabs',
  );

  // Location and Service Time
  $form['location-service-time'] = array(
    '#type' => 'fieldset',
    '#group' => 'group',
    '#title' => t('Location/Service Time'),
  );

    $form['location-service-time']['address'] = array(
      '#type' => 'textfield',
      '#title' => t('Address'),
      '#size' => '100',
      '#maxlength' => '300',
      '#default_value' => empty($var['address']) ? '' : $var['address'],
    );

    $form['location-service-time']['service-time'] = array(
      '#type' => 'textfield',
      '#size' => '100',
      '#title' => t('Service Time'),
      '#maxlength' => 300,
      '#default_value' => empty($var['service-time']) ? '' : $var['service-time'],
    );

    $form['location-service-time']['locate'] = array(
      '#type' => 'submit',
      '#submit' => array(),
      '#value' => t('Locate'),
      '#ajax' => array(
        'callback' => 'map_locate',
        'wrapper' => 'locate',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );

    $form['location-service-time']['geometry'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t("Google Maps Location Stuff"),
      '#prefix' => '<div id="locate">',
      '#suffix' => '</div>',

    );

    $form['location-service-time']['geometry']['lat'] = array(
      '#type' => 'textfield',
      '#maxlength' => 100,
      '#default_value' => empty($var['lat']) ? '' : $var['lat'],
    );

    $form['location-service-time']['geometry']['long'] = array(
      '#type' => 'textfield',
      '#maxlength' => 100,
      '#default_value' => empty($var['long']) ? '' : $var['long'],
    );

    $form['sermon-promo'] = array(
      '#type' => 'fieldset',
      '#group' => 'group',
      '#title' => t('Sermon Promo'),
    );


    if (empty($var['sermon'])) {

      $value = '';

    } else {

      $value = '[' . $var['sermon'] . ']';
      $node = node_load($var['sermon']);
      $value = $node->title . " " . $value;

    }

    $form['sermon-promo']['sermon'] = array(
      '#type' => 'textfield',
      '#size' => '60',
      '#title' => t('Sermon to display on the homepage'),
      '#maxlength' => 300,
      '#autocomplete_path' => 'sermon/autocomplete',
      '#default_value' => $value,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Configuration'),
    );

    return $form;

}

/**
 * Menu callback for AJAX additions.
 */
function map_locate($form, $form_state) {
  $url = 'https://maps.googleapis.com/maps/api/geocode/json?address=' .
    str_replace(' ', '+', $form_state['values']['address'])
    . '&key=' .
    'AIzaSyDS_GtfssENJ_tjGAfu3fTZpj1T8ODTtBo';  // Google Maps API KEY;

  $json = file_get_contents($url);
  $config = json_decode($json, TRUE);

  if ($config['status'] = "OK") {
    $result = reset($config["results"]);

    $form['location-service-time']['geometry']['lat']['#value']  =
    $form['location-service-time']['geometry']['lat']['#default_value'] =
      $result['geometry']['location']['lat'];
    $form['location-service-time']['geometry']['long']['#value'] = $result['geometry']['location']['lng'];
  } else {
    drupal_set_message(t('Geolocation API didn\'t work!'), 'warning', FALSE);
  }

  return $form['location-service-time']['geometry'];
}

/**
 * [portico_config_submit description]
 * @param  [type] $form        [description]
 * @param  [type] &$form_state [description]
 * @return [type]              [description]
 */
function portico_config_submit($form, &$form_state) {
  $values = $form_state['values'];

  if (!empty($values['sermon'])) {
    $matches = array();
    if (preg_match('/(\w+)(?=\])/', $values['sermon'], $matches)) {
      $values['sermon'] = $matches[0];
    } else {
      unset($values['sermon']);
    }
  }

  variable_set('portico_config', $values);
  drupal_set_message(t('Configuration Saved.'), 'status', FALSE);
}

/**
 * [portico_now_table description]
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function portico_now_table($form, $form_state) {
  $weights = variable_get('portico_structure_portico_now_weights', array());

  $nids = db_select('node', 'n')
        ->condition('n.type', 'portico_now')
        ->fields('n',array('nid'))
        ->execute()
        ->fetchCol();

  $nodes = node_load_multiple($nids);
  $destination = drupal_get_destination();

  $form['rows']['#tree'] = TRUE;

  foreach ($nodes as $node) {

    $form['rows'][$node->nid] = array(
      // 'class' => array('draggable'),
      'title' => array(
        '#markup' => $node->title
        // '#suffix' => ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed))),
      ),
      'status' => array(
        '#type' => 'markup',
        '#markup' => $node->status ? 'Published' : 'Not Published',
      ),
      'weight' => array(
        '#type' => 'weight',
        '#default_value' => $weights[$node->nid]['weight'],
        '#delta' => 50,
      ),
    );

    $operations = array(
      'edit' => array(
        'title' => t('edit'),
        'href' => 'node/' . $node->nid . '/edit',
        'query' => $destination,
      ),
      'delete' => array(
        'title' => t('delete'),
        'href' => 'node/' . $node->nid . '/delete',
        'query' => $destination,
      ),
    );

    $form['rows'][$node->nid]['operations'] = array();
    // Render an unordered list of operations links.
    $form['rows'][$node->nid]['operations'] = array(
      '#theme' => 'links__node_operations',
      '#links' => $operations,
      '#attributes' => array('class' => array('links', 'inline')),
    );
  }

  uasort($form['rows'], '_weight_form_sort');

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));

  return $form;
}

/**
 * [_weight_form_sort description]
 * @param  [type] $a [description]
 * @param  [type] $b [description]
 * @return [type]    [description]
 */
function _weight_form_sort($a,$b) {
  return $a['weight']['#default_value']>$b['weight']['#default_value'];
}

/**
 * [portico_now_table_submit description]
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function portico_now_table_submit($form, $form_state) {
  variable_set('portico_structure_portico_now_weights', $form_state['values']['rows']);
  drupal_flush_all_caches();
}

/**
 * [theme_portico_now_table description]
 * @param  [type] $form [description]
 * @return [type]       [description]
 */
function theme_portico_now_table(&$vars) {
    // the variable that will hold our form HTML output
    $output = '';
    $table_rows = array();

    $form = &$vars['form'];

    //loop through each "row" in the table array
    foreach(element_children($form['rows']) as $nid) {
        // this array will hold the table cells for a row
        $this_row = array();

        // first, add the "name" markup
        $this_row[] = drupal_render($form['rows'][$nid]['title']);
        $this_row[] = drupal_render($form['rows'][$nid]['status']);

        // Add the weight field to the row
        // the Javascript to make our table drag and drop will end up hiding this cell
        $form['rows'][$nid]['weight']['#attributes']['class'] = array('portico-now-weight');
        $this_row[] = drupal_render($form['rows'][$nid]['weight']);
        $this_row[] = drupal_render($form['rows'][$nid]['operations']);

        //Add the row to the array of rows
        $table_rows[] = array('data' => $this_row, 'class' => array('draggable'));
    }

    // Make sure the header count matches the column count
    $header = array(
      t('Name'),
      t('Status'),
      t('Weight'),
      t('Operations'),
    );

    $table_id = 'portico-now-table-id';

    // over-write the 'rows' form element with the markup generated from our table
    $form['rows'] = array(
      '#markup' => theme('table', array('header' => $header, 'rows' => $table_rows, 'attributes' => array('id' => $table_id))),
    );

    // render the form
    // note, this approach to theming the form allows you to add other elements in the method
    // that generates the form, and they will automatically be rendered correctly
    $output .= drupal_render_children($form);

    // this function is what brings in the javascript to make our table drag-and-droppable
    drupal_add_tabledrag($table_id, 'order', 'sibling', 'portico-now-weight');

    return $output;
}
