<?php
/**
 * @file
 * portico_now.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function portico_now_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_portico_now_category'.
  $field_bases['field_portico_now_category'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_portico_now_category',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'portico_now_category',
          'parent' => 0,
        ),
      ),
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
