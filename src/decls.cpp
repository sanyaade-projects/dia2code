/*
This file is part of dia2code. It generates code from an UML Dia Diagram.
Copyright (C) 2000-2014

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "decls.hpp"

#include "umlPackage.hpp"

module *
create_nested_modules_from_pkglist (std::list <umlPackage> &pkglist,
                                    module        *m)
{
    bool first = true;
    /* Expects pkglist and m to be non-NULL and m->contents to be NULL.
       Returns a reference to the innermost module created.  */
    for (umlPackage & it : pkglist) {
        if (first)
        {
            first = false;
            continue;
        }
        declaration d;
        d.decl_kind = dk_module;
        d.u.this_module = new module;
        m->contents.push_back(d);
        m = d.u.this_module;
        m->pkg = it;
    }
    return m;
}


module *
find_or_add_module (std::list <declaration> &dptr,
                    std::list <umlPackage> &pkglist)
{
    declaration d;
    module *m;

    if (pkglist.empty ())
        return NULL;
    
    for (declaration & it : dptr) {
        if (it.decl_kind == dk_module &&
            it.u.this_module->pkg.getName ().compare ((*pkglist.begin ()).getName ()) == 0) {
            m = it.u.this_module;
            if (pkglist.size () == 1)
                return m;
            if (m->contents.empty ()) {
                return create_nested_modules_from_pkglist (pkglist, m);
            }
            return find_or_add_module (m->contents, pkglist);
        }
    }
    d.decl_kind = dk_module;
    d.u.this_module = new module;
    m = d.u.this_module;
    m->pkg = *pkglist.begin ();
    dptr.push_back (d);

    return create_nested_modules_from_pkglist (pkglist, m);
}





/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
