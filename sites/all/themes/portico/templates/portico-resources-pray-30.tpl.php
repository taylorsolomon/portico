<?php

$uri  = 'public://';
$url = file_create_url($uri);

$num_images = 5;
$prefix = 'Pray30_';

$type_map = array(
  array(
    'type' => 'Phone',
    'size' => '640x1136',
  ),
  array(
    'type' => 'Tablet',
    'size' => '1536x2048',
  ),
  array(
    'type' => 'Desktop',
    'size' => '5120x2880',
  ),
);

?>
<div class='resources'>
<?php foreach($type_map as $type): ?>

  <h3><?php print $type['type']; ?></h3>

  <?php foreach(range(1, $num_images) as $num): ?>
    <?php $href = $url . 'pray-30/' . $prefix . $type['type'] . 'BG_' . $type['size'] . '_' . $num . '.jpg'; ?>
    <a href="<?php print $href; ?>" target="_blank">$href</a>
  <?php endforeach; ?>

<?php endforeach; ?>

</div>
