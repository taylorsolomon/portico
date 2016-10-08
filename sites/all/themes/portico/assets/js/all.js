var porticoConfig = {
  test: false,
},
themePath = '/sites/all/themes/portico',
assetPath = '/sites/all/themes/portico/assets/js/vendor';

/**
 * [loadAsset description]
 * @param {[type]}   filename [description]
 * @param {Function} callback [description]
 */
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

    // Call sticky header
    stickyHeader();

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

          $(this).addClass('open').siblings('.blog-facets-wrapper').height(height);
        }
      });
    }


    // FitVids
    if ($('iframe').length) {
      loadAsset(themePath + '/bower_components/jquery.fitvids/jquery.fitvids.js', function() {
        $('#page-wrapper').fitVids();
      });
    }

    porticoNowScroll();

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

  /**
   * Small sticky header implementation
   * @return {[type]} [description]
   */
  function stickyHeader() {

    var heightOffset = 200,
        isDesktop = $(window).width() > 720 ? true : false;

    if (isDesktop) {

      var stickyMenu = $('.menu-name-main-menu').clone().addClass('sticky');
      $('body').append(stickyMenu);

      $(window).on('scroll', function() {
        var fromTop = $(document).scrollTop();
        if (fromTop - heightOffset >= 0) {
          stickyMenu.addClass('down');
        } else {
          stickyMenu.removeClass('down');
        }
      });
    }
  }


  // Project Scroll thing
  function porticoNowScroll() {
    if (!$('.jump-list').find('li').length) {
      return true;
    }
    var doneScrolling = true;

    $('.jump-list').children('li').first().addClass('selected');

    $('.jump-list').on('click', 'a', function(e) {
      e.preventDefault();
      doneScrolling = false;
      $(e.target).parent('li').addClass('selected').siblings().removeClass('selected');

      var position = $(e.target).parent().index();

      var offset;

      var component = $('.node-page .content').children().eq(position);

      if (position === 0) {
        offset = component.offset().top - 100;
      } else {
        offset = component.offset().top - 60;
      }

      $('body, html').animate({
        scrollTop: offset
        },
        {
        complete: function() {
          setTimeout(function() {
            doneScrolling = true;
          }, 100);
        }
      }, 400);
    });

    var scrollerFixed = false,
        projects = [];

    $('article.node-portico-now').each(function(index, el) {
      projects.push(Math.round($(el).offset().top));
    });


    $(window).on('scroll', function() {

      if (($('#main').offset().top - $(window).scrollTop() - 40) < 0 && !scrollerFixed) {
        $('#sidebar-first .item-list').addClass('fixed');
        scrollerFixed = true;
      }

      if (($('#main').offset().top - $(window).scrollTop() - 40) > 0 && scrollerFixed) {
        $('#sidebar-first .item-list').removeClass('fixed');
        scrollerFixed = false;
      }

      if (doneScrolling) {
        projects.map(
          function(val, index, array) {
            if ($(window).scrollTop() >= val) {
              this.children(':eq('+ index +')').addClass('selected').siblings().removeClass('selected');
            }
          },
          $('#sidebar-first .item-list').find('ul').first()
        );
      }
    });
  }

})( jQuery, window, document );
