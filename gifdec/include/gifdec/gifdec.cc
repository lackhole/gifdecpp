//
// Created by YongGyu Lee on 2021/06/23.
//

#include "gifdec/gifdec.h"

#include <cstring>

#include <vector>

#include "gifdec/c/gifdec_c.h"

namespace gif {

namespace {

inline gd_GIF* cast_gif(void *p) {
  return static_cast<gd_GIF*>(p);
}

} // anonymous namespace

GIFDecoder::GIFDecoder(const std::string &path) {
  open(path);
}

GIFDecoder::~GIFDecoder() {
  close();
}

void GIFDecoder::open(const std::string &path) {
  close();
  pImpl = gd_open_gif(path.c_str());
  if (is_open()) {
    buffer.resize(width() * height() * 3);
  }
}

void GIFDecoder::close() {
  if (pImpl) {
    gd_close_gif(cast_gif(pImpl));
    pImpl = nullptr;
  }
}

int GIFDecoder::width() const {
  return cast_gif(pImpl)->width;
}

int GIFDecoder::height() const {
  return cast_gif(pImpl)->height;
}

bool GIFDecoder::is_open() const {
  return pImpl != nullptr;
}

bool GIFDecoder::grab_next(uint8_t *dst) {
  auto gif = cast_gif(pImpl);
  auto buf = buffer.data();
  int size = width() * height();

  if (!gd_get_frame(gif))
    return false;

  gd_render_frame(gif, buf);
  int i = 0, temp;
  while (i < size) {
    if (gd_is_bgcolor(gif, buf + i*3)) {
      temp = i;
      ++i;

      while (i < size && gd_is_bgcolor(gif, buf + i*3)) {
        ++i;
      }
      std::memset(dst + temp*4, 0, (i - temp) * 4);
    } else {
      std::memcpy(dst + i*4, buf + i*3, 3);
      dst[i*4 + 3] = 255;
      ++i;
    }
  }

  return true;
}

bool GIFDecoder::grab_next_rgb(uint8_t* dst) {
  auto gif = cast_gif(pImpl);

  if (!gd_get_frame(gif))
    return false;

  gd_render_frame(gif, buffer.data());
  std::memcpy(dst, buffer.data(), width() * height() * 3);
  return true;
}

int GIFDecoder::current_delay() const {
  return cast_gif(pImpl)->gce.delay * 10;
}

void GIFDecoder::rewind() {
  gd_rewind(cast_gif(pImpl));
}

int GIFDecoder::loop_count() const {
  return cast_gif(pImpl)->loop_count;
}

} // namespace gif
