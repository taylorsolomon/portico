// Include gulp
var gulp         = require('gulp');
var path         = require('path');

// Include Our Plugins
var livereload   = require('gulp-livereload');
var sass         = require('gulp-sass');
var prefix       = require('gulp-autoprefixer');
var jshint       = require('gulp-jshint');
var concat       = require('gulp-concat');
var uglify       = require('gulp-uglify');
var rename       = require('gulp-rename');
var gutil        = require('gulp-util');
var beep         = require('beepbeep');
var neat         = require('node-neat');
var plumber      = require('gulp-plumber');

// JS error handling
var onError = function (err) {
  beep([0, 0, 0]);
  gutil.log(
    gutil.colors.yellow(err)
  );
};

//libsass
gulp.task('sass', function () {
    return gulp.src('./dev/scss/main.scss')
        .pipe(sass({
            includePaths: [

            ],
            outputStyle: 'expanded', // change to compressed when you're done
            errLogToConsole: true
        }))
        .pipe(prefix())
        .pipe(gulp.dest('./assets/css'))
        .pipe(livereload())
});

gulp.task('sass', function () {
  gulp.src('./dev/scss/main.scss')
    .pipe(sass({
      // includePaths: require('node-bourbon').with('other/path', 'another/path')
      // - or -
      includePaths: neat.includePaths,
      outputStyle: 'expanded', // change to compressed when you're done
    }).on('error', onError))
    .pipe(gulp.dest('./assets/css'));
});

// Lint Task
gulp.task('lint', function() {
	return gulp.src('./dev/js/*.js')
		.pipe(jshint())
		.pipe(jshint.reporter('default'));
});


// Concatenate & Minify JS

gulp.task('scripts', function() {
	return gulp.src('./dev/js/*.js')
		.pipe(concat('all.js'))
		.pipe(gulp.dest('./assets/js'))
		.pipe(rename('all.min.js'))
    .pipe(plumber({ errorHandler: onError }))
		.pipe(uglify())
		.pipe(gulp.dest('./assets/js'))
		.pipe(livereload());
});

// Watch Files For Changes
gulp.task('watch', function() {
	livereload({start: true});
  livereload.listen();
  gutil.log(livereload.server);

	// Watch for js changes
	gulp.watch('./dev/js/*.js', ['lint', 'scripts']);

	// Watch for scss changes
	gulp.watch('./dev/**/*.scss', ['sass']);

});


// Default Task
gulp.task('default', ['sass', 'lint', 'scripts', 'watch']);
