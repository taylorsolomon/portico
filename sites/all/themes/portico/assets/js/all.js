var porticoConfig = {};


;(function ( $, window, document, undefined ) {

  "use strict";

    $(document).ready(function() {

      // Sermon toggle JS
      if ($('.sermon-body-toggle').length) {
        $('.sermon-body-toggle').on('click', function(e) {
          e.preventDefault();
          if ($(this).hasClass('open')) {
            $(this).removeClass('open').siblings('.sermon-body').height('');
          } else {
            var body = $(this).siblings('.sermon-body').children('.field-body').height();
            $(this).addClass('open').siblings('.sermon-body').height(body);
          }
        });
      }
      
    });

  })( jQuery, window, document );
