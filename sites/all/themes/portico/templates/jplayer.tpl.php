<?php
/**
 * @file
 * Provide the HTML output for a jPlayer interface.
 */
?>

<div class="jp-<?php print $type; ?>">
  <div class="jp-type-playlist">
    <div id="<?php print $player_id; ?>" class="jp-jplayer"></div>
    <div id="<?php print $player_id; ?>_interface" class="jp-interface">

      <ul class="jp-controls">
        <li><a href="#" class="jp-play" tabindex="1"><span>play</span></a></li>
        <li><a href="#" class="jp-pause" tabindex="1"><span>pause</span></a></li>
      </ul>

      <div class="jp-progress">
        <div class="jp-seek-bar">
          <div class="jp-play-bar"></div>
        </div>
      </div>

      <div class="jp-current-time"></div>
      <div class="jp-duration"></div>
    </div>

  </div>
</div>

<?php if($dynamic !== TRUE): ?>
<?php print drupal_render($dynamic);?>
<?php endif; ?>
