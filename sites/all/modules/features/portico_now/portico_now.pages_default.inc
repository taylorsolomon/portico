<?php
/**
 * @file
 * portico_now.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function portico_now_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__http_response_d8792447-0b33-453f-94bb-55dc3e68c741';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'http_response';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Portico Now',
    'contexts' => array(),
    'relationships' => array(),
    'code' => '404',
    'destination' => '',
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'portico_now' => 'portico_now',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $export['node_view__http_response_d8792447-0b33-453f-94bb-55dc3e68c741'] = $handler;

  return $export;
}
