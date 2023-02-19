#!/bin/sh

DIST=$PWD/dist

make_dist() {
    cd ${DIR:-$PROJECT}
    git archive -o $DIST/$PROJECT-$VERSION.zip \
        --prefix=$PROJECT-$VERSION/ --add-file=../LICENSE_MPL-2.0.txt --add-file=../LICENSE_CC0-1.0.txt HEAD .
    cd $DIST
    sha256sum -b $PROJECT-$VERSION.zip > $PROJECT-$VERSION.zip.sha256sum
}

[ ! -d "$DIST" ] && mkdir "$DIST" || rm "$DIST"/*

(PROJECT=libseven VERSION=0.17.2 make_dist)
(PROJECT=minrt VERSION=0.7.3 make_dist)
