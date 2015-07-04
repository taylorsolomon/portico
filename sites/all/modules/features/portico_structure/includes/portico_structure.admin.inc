<?php

function portico_config($form, &$form_state) {
  $var = variable_get('portico_config', '');

  $form['group'] = array(
    '#type' => 'vertical_tabs',
  );

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

function portico_config_submit($form, &$form_state) {
  $values = $form_state['values'];

  variable_set('portico_config', $values);
  drupal_set_message(t('Configuration Saved.'), 'status', FALSE);
}