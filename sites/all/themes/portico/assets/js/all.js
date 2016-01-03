var porticoConfig = {

  test: true,
},
themePath = '/sites/all/themes/portico',
assetPath = '/sites/all/themes/portico/assets/js/vendor/';

function loadAsset(filename, callback){
  var script = document.createElement('script');
  script.setAttribute("type","text/javascript");

  if (script.readyState){ //IE
    script.onreadystatechange = function(){
      if (script.readyState == "loaded" || script.readyState == "complete") {
        script.onreadystatechange = null;
        callback();
      }
    };
  } else { //Others
    script.onload = function(){
      callback();
    };
  }

  script.setAttribute("src", filename);

  if (typeof script !== "undefined") {
    document.getElementsByTagName("head")[0].appendChild(script);
  }
}

;(function ( $, window, document, undefined ) {

  "use strict";

    $(document).ready(function() {
      
      loadAsset(themePath + '/bower_components/slideout.js/dist/slideout.js', mobileMenu);

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

    var mobileMenu = function() {

      var menu   = $('#block-menu-block-main-menu').find('.menu-block-wrapper > ul'),
          markup = menu.clone();

      markup.attr('id', 'mobile-menu');

      porticoConfig.menu = new Slideout({
        'panel': document.getElementById('page-wrapper'),
        'menu': document.getElementById('off-screen-nav'),
        'padding': 256,
        'tolerance': 70,
        'side': 'right',
        'duration': 200,
        // 'fx': 'cubic-bezier(0.5,0.8,0.5,0.8)'
      });

      markup.appendTo('#off-screen-nav');
      console.log($('#off-screen-nav'));
      porticoConfig.menu.on('beforeopen', function() {
        $('#off-screen-bounds').addClass('open');

      }).on('beforeclose', function() {
        $('#off-screen-bounds').removeClass('open');
      });

      var div = document.createElement('div');
      div.setAttribute('id', 'off-screen-bounds');
      document.getElementsByTagName("body")[0].appendChild(div);

      $('#off-screen-bounds').on('click touchstart', function(e) {
        porticoConfig.menu.close();
      });

      $('#trigger-menu').on('click', function(e) {
        e.preventDefault();
        porticoConfig.menu.open();
      });
    };

  })( jQuery, window, document );
