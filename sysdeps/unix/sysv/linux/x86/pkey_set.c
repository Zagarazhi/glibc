/* Changing the per-thread memory protection key, x86_64 version.
   Copyright (C) 2017-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <arch-pkey.h>
#include <errno.h>
#include <sys/mman.h>

int
__pkey_set (int key, unsigned int rights)
{
  if (key < 0 || key > 15 || rights > 3)
    {
      __set_errno (EINVAL);
      return -1;
    }
  unsigned int mask = 3 << (2 * key);
  unsigned int pkru = pkey_read ();
  pkru = (pkru & ~mask) | (rights << (2 * key));
  pkey_write (pkru);
  return 0;
}
libc_hidden_def (__pkey_set)
weak_alias (__pkey_set, pkey_set)
