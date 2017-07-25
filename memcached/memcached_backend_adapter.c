/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * In addition to the permissions in the GNU General Public License,
 * the authors give you unlimited permission to link the compiled
 * version of this file into combinations with other programs,
 * and to distribute those combinations without any restriction
 * coming from the use of this file.  (The General Public License
 * restrictions do apply in other respects; for example, they cover
 * modification of the file, and distribution when not linked into
 * a combined executable.)
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <git2.h>
#include <git2/sys/odb_backend.h>
#include <stdio.h>
#include "memcached.h"

int attach_memcached_to_repo(git_repository* repo, const char *host, int port) {

    git_odb_backend* odb_backend = NULL;

    int er = git_odb_backend_memcached(&odb_backend, host, port);
    if (er < 0) {
        return er;
    }
    git_odb *odb = NULL;
    er = git_odb_new(&odb);
    if (er < 0) {
        return er;
    }
    er = git_odb_add_backend(odb, odb_backend, 0);
    if (er < 0) {
        git_odb_free(odb);
        return er;
    }

    git_repository_set_odb(repo, odb);

    git_odb_free(odb);
    return er;
}

int give_me_five() {
    printf("Hey Yo!\n");
    return 5;
}
