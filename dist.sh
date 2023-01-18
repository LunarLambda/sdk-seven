#!/bin/sh

DIST=$PWD/dist

make_dist() {
    cd ${DIR:-$PROJECT}
    git archive -o $DIST/$PROJECT-$VERSION.zip --prefix=$PROJECT-$VERSION/ HEAD .
    cd $DIST
    sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
}

[ ! -d "$DIST" ] && mkdir "$DIST" || rm "$DIST"/*

(PROJECT=libseven VERSION=0.13.0 make_dist)
(PROJECT=minrt VERSION=0.5.0 make_dist)
