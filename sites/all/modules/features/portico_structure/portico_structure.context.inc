<?php
/**
 * @file
 * portico_structure.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function portico_structure_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'front';
  $context->description = 'Frontpage';
  $context->tag = 'Portico';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'portico_structure-location' => array(
          'module' => 'portico_structure',
          'delta' => 'location',
          'region' => 'content',
          'weight' => '-10',
        ),
        'portico_structure-sermon_promo' => array(
          'module' => 'portico_structure',
          'delta' => 'sermon_promo',
          'region' => 'content',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Frontpage');
  t('Portico');
  $export['front'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide';
  $context->description = 'Sitewide Block Placement';
  $context->tag = 'Portico';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => '1',
          'region' => 'hero',
          'weight' => '-10',
        ),
        'portico_structure-hero_image_title' => array(
          'module' => 'portico_structure',
          'delta' => 'hero_image_title',
          'region' => 'hero',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Portico');
  t('Sitewide Block Placement');
  $export['sitewide'] = $context;

  return $export;
}