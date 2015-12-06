<?php
/**
 * @file
 * portico_blog.features.inc
 */

/**
 * Implements hook_node_info().
 */
function portico_blog_node_info() {
  $items = array(
    'blogpost' => array(
      'name' => t('Blogpost'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
