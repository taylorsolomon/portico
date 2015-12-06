<?php
/**
 * @file
 * portico_blog.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function portico_blog_taxonomy_default_vocabularies() {
  return array(
    'blogpost_category' => array(
      'name' => 'Blogpost Category',
      'machine_name' => 'blogpost_category',
      'description' => 'List of Blogpost Categories',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
