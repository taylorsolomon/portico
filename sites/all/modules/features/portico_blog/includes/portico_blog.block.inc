<?php
/**
 * @file
 * portico_blog.block.inc
 */

/**
 * Implements hook_block_info().
 */
function portico_blog_block_info() {

  $blocks['blog_featured'] = array(
    'info' => t('Featured Blog Posts'),
    'cache' => DRUPAL_CACHE_GLOBAL
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function portico_blog_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'blog_featured':
      $block['subject'] = '<none>';
      $block['content'] = portico_blog_blog_featured();
      break;

  }
  return $block;
}

/**
 * [portico_blog_blog_featured description]
 * @return [type] [description]
 */
function portico_blog_blog_featured() {
  $q = new EntityFieldQuery;
  $q->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'blogpost')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyCondition('promote', TRUE)
    ->range(NULL,2)
    ->propertyOrderBy('created', 'DESC')
    ->addTag('portico_blog_blog_featured');

  $r = $q->execute();
  if (empty($r['node'])) {
    return FALSE;
  }

  $nodes = entity_load('node', array_keys($r['node']));
  $viewed = entity_view('node', $nodes, 'blog_teaser');

  return $viewed;
}