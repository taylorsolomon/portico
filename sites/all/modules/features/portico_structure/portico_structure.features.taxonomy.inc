<?php
/**
 * @file
 * portico_structure.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function portico_structure_taxonomy_default_vocabularies() {
  return array(
    'series' => array(
      'name' => 'Series',
      'machine_name' => 'series',
      'description' => 'Vocabulary of Series. Sermons are attached to Series',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
