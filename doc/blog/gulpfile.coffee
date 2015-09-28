###
  Created by Pavel on 01.09.2015.
###

gulp = require 'gulp'
clean = require 'gulp-clean'
connect = require 'gulp-connect'
run_sequence = require 'run-sequence'
gh_pages = require 'gulp-gh-pages'

# Delete all files in dist
gulp.task 'clean', ->
    gulp.src './build/*'
    .pipe clean()

gulp.task 'deploy', ->
  gulp.src './build/**/*'
  .pipe gh_pages
    force: true


gulp.task 'connect', ->
  connect.server
    root: './build'
    livereload: true

# Copy html
gulp.task 'html', ->
  gulp.src './app/*.html'
  .pipe gulp.dest './build'
  .pipe connect.reload()

gulp.task 'imgs', ->
  gulp.src './app/img/*.png'
  .pipe gulp.dest './build/img'
  .pipe connect.reload()

# Copy java script files
gulp.task 'js', ->
  gulp.src 'bower_components/bootstrap/dist/js/*.min.js'
  .pipe gulp.dest './build/js'
  .pipe connect.reload()

# Copy css files
gulp.task 'css', ->
  gulp.src 'bower_components/bootstrap/dist/css/*.min.css'
  .pipe gulp.dest './build/css'
  .pipe connect.reload()

gulp.task 'build', (callback)->
  run_sequence 'clean', ['html', 'imgs', 'js', 'css'], callback

gulp.task 'watch', ->
  gulp.watch ['./app/*.html'], ['build']

gulp.task 'default', ['connect', 'build', 'watch']