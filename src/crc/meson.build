# Copyright (C) 2019-2023 by Sukchan Lee <acetcom@gmail.com>

# This file is part of Open5GS.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

libcrc_sources = files('crc.c', 'crc.h')

libcrcmetrics_sources = files('crc_metrics_example.c', 'crc_metrics_example.h','metrics.h','metrics.c')

libcrcmetrics = static_library('crc_metrics',
    sources : libcrcmetrics_sources,
    include_directories : include_directories('.'),
    dependencies : [libmetrics_dep],
    install : false
)

libcrc = static_library('crc',
    sources : libcrc_sources,
    include_directories : include_directories('.'),
    install : false
)



