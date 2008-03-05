/*
 * File format: HTK   (c) 2008 robs@users.sourceforge.net
 *
 * See http://labrosa.ee.columbia.edu/doc/HTKBook21/HTKBook.html
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, write to the Free Software Foundation,
 * Fifth Floor, 51 Franklin Street, Boston, MA 02111-1301, USA.
 */

#include "sox_i.h"
#include <math.h>

typedef enum {
  Waveform, Lpc, Lprefc, Lpcepstra, Lpdelcep, Irefc,
  Mfcc, Fbank, Melspec, User, Discrete, Unknown} kind_t;
static char const * const str[] = {
  "Sampled waveform", "Linear prediction filter", "Linear prediction",
  "LPC cepstral", "LPC cepstra plus delta", "LPC reflection coef in",
  "Mel-frequency cepstral", "Log mel-filter bank", "Linear mel-filter bank",
  "User defined sample", "Vector quantised data", "Unknown"};

static int start_read(sox_format_t * ft)
{
  uint32_t period_100ns, num_samples;
  uint16_t bytes_per_sample, parmKind;

  if (sox_readdw(ft, &num_samples     ) ||
      sox_readdw(ft, &period_100ns    ) ||
      sox_readw (ft, &bytes_per_sample) ||
      sox_readw (ft, &parmKind        )) return SOX_EOF;
  if (parmKind != Waveform) {
    int n = min(parmKind & 077, Unknown);
    sox_fail_errno(ft, SOX_EFMT, "unsupported HTK type `%s' (0%o)", str[n], parmKind);
    return SOX_EOF;
  }
  return sox_check_read_params(ft, 1, 1e7 / period_100ns,
      SOX_ENCODING_SIGN2, (unsigned)bytes_per_sample << 3, (off_t)num_samples);
}

static int write_header(sox_format_t * ft)
{
  double period_100ns = 1e7 / ft->signal.rate;

  if (!ft->olength && floor(period_100ns) != period_100ns)
    sox_warn("rounding sample period %f (x 100ns) to nearest integer", period_100ns);
  return sox_writedw(ft, ft->olength? ft->olength:ft->length)
      || sox_writedw(ft, (uint32_t)(period_100ns + .5))
      || sox_writew(ft, ft->encoding.bits_per_sample >> 3)
      || sox_writew(ft, Waveform) ? SOX_EOF : SOX_SUCCESS;
}

SOX_FORMAT_HANDLER(htk)
{
  static char const * const names[] = {"htk", NULL};
  static unsigned const write_encodings[] = {SOX_ENCODING_SIGN2, 16, 0, 0};
  static sox_format_handler_t handler = {
    names, SOX_FILE_BIG_END | SOX_FILE_MONO | SOX_FILE_REWIND,
    start_read, sox_rawread, NULL,
    write_header, sox_rawwrite, NULL,
    sox_rawseek, write_encodings, NULL
  };
  return &handler;
}