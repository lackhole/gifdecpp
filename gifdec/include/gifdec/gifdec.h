//
// Created by YongGyu Lee on 2021/06/23.
//

#ifndef GIFDEC_GIF_DECODER_H_
#define GIFDEC_GIF_DECODER_H_

#include <cstdint>

#include <string>
#include <vector>

#if __cplusplus >= 201703L
# define GIFDEC_NODISCARD_CXX17 [[nodiscard]]
#else
# define GIFDEC_NODISCARD_CXX17
#endif

namespace gif {

class GIFDecoder {
 public:
  GIFDecoder() = default;
  ~GIFDecoder();

  /**
   * Effectively calls open(path)
   * @param path
   */
  explicit GIFDecoder(const std::string& path);

  /**
   * Opens the GIF file
   * @param path path to the file
   */
  void open(const std::string& path);

  /**
   * Closes the GIF file
   */
  void close();

  /**
   * Check if the file is opened.
   * @return true if opened
   */
  GIFDEC_NODISCARD_CXX17 bool is_open() const;

  explicit operator bool() const { return is_open(); }

  /** Note that it's undefined behavior to call the below functions if the file is not opened. */

  /**
   * Returns width of the GIF
   * @return width in pixels
   */
  GIFDEC_NODISCARD_CXX17 int width() const;

  /**
   * Returns height of the GIF
   * @return height in pixels
   */
  GIFDEC_NODISCARD_CXX17 int height() const;

  /**
   * Copy next RGBA frame to dst.
   * dst must be allocated with [sizeof(uint8_t) * width() * height() * 4] bytes
   * Note that the value of the alpha channel is 0 or 255 only.
   *
   * @param dst copy destination
   * @return false if reached to the end
   */
  bool grab_next(uint8_t* dst);

  /**
   * Copy next RGB frame to dst.
   * dst must be allocated with [sizeof(uint8_t) * width() * height() * 3] bytes
   *
   * @param dst copy destination
   * @return false if reached to the end
   */
  bool grab_next_rgb(uint8_t* dst);

  /**
   * Returns current frame's delay in milliseconds
   * @return current frame's delay in milliseconds
   */
  int current_delay() const;

  /**
   * Roll back to the first frame.
   */
  void rewind();

  /**
   * Loop count of the GIF
   * @return loop count
   */
  GIFDEC_NODISCARD_CXX17 int loop_count() const;

 private:
  void* pImpl = nullptr;
  std::vector<uint8_t> buffer;
};

} // namespace gif

#endif // GIFDEC_GIF_DECODER_H_
