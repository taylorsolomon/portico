<?php
/**
 * @file
 * portico_now.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function portico_now_taxonomy_default_vocabularies() {
  return array(
    'portico_now_category' => array(
      'name' => 'Portico Now Category',
      'machine_name' => 'portico_now_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
