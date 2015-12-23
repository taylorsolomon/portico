var porticoConfig = {};


;(function ( $, window, document, undefined ) {

  "use strict";

    $(document).ready(function() {

      // Sermon toggle JS
      if ($('.sermon-body-toggle').length) {
        $('.sermon-body-toggle').on('click touchstart', function(e) {
          e.preventDefault();
          if ($(this).hasClass('open')) {
            $(this).removeClass('open').siblings('.sermon-body').height('');
          } else {
            var body = $(this).siblings('.sermon-body').children('.field-body').height();
            $(this).addClass('open').siblings('.sermon-body').height(body);
          }
        });
      }

      if ($('.filter-bar').length) {
        $('.filter-bar').on('click touchstart', function(e) {
          e.preventDefault();
          if ($(this).hasClass('open')) {
            $(this).removeClass('open').siblings('.blog-facets-wrapper').height('');
          } else {
            var height = $(this).siblings('.blog-facets-wrapper').children('.blog-facets').height();
            console.log(height);
            $(this).addClass('open').siblings('.blog-facets-wrapper').height(height);
          }
        });
      }
    });

  })( jQuery, window, document );
