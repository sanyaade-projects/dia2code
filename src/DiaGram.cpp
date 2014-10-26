/*
Copyright (C) 2014-2014

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "config.h"

#include "DiaGram.hpp"

DiaGram::DiaGram () :
  license (),
  outdir ("."),
  overwrite (true),
  buildtree (false),
  invertsel (false)
{
}


char *
DiaGram::getLicense ()
{
    return license.c_str ();
}


void
DiaGram::setLicense (char * lic)
{
    license.assign (lic);

    return;
}


char *
DiaGram::getOutdir ()
{
    return outdir.c_str ();
}


const std::string *
DiaGram::getOutdirS ()
{
    return &outdir;
}


void
DiaGram::setOutdir (char * dir)
{
    outdir.assign (dir);

    return;
}


bool
DiaGram::getOverwrite ()
{
    return overwrite;
}


void
DiaGram::setOverwrite (bool over)
{
    overwrite = over;

    return;
}


bool
DiaGram::getBuildTree ()
{
    return buildtree;
}


void
DiaGram::setBuildTree (bool build)
{
    buildtree = build;

    return;
}


bool
DiaGram::getInvertSel ()
{
    return invertsel;
}


void
DiaGram::setInvertSel (bool invert)
{
    invertsel = invert;

    return;
}


DiaGram::~DiaGram ()
{
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */