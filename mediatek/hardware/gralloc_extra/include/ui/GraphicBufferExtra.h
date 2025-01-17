#ifndef MTK_GRALLOC_EXTRA_GRAPHIC_BUFFER_EXTRA_H
#define MTK_GRALLOC_EXTRA_GRAPHIC_BUFFER_EXTRA_H

#include <stdint.h>
#include <sys/types.h>

#include <utils/Singleton.h>

#include <hardware/gralloc_extra.h>

namespace android {
// ---------------------------------------------------------------------------
class GraphicBuffer;

class GraphicBufferExtra : public Singleton<GraphicBufferExtra>
{
public:
    static inline GraphicBufferExtra& get() { return getInstance(); }

    GRALLOC_EXTRA_RESULT query(buffer_handle_t handle, GRALLOC_EXTRA_ATTRIBUTE_QUERY attribute, void *out_pointer);
    GRALLOC_EXTRA_RESULT perform(buffer_handle_t handle, GRALLOC_EXTRA_ATTRIBUTE_PERFORM attribute, void *in_pointer);

    /** Deprecated methods
     * please use query/perform instead of using the following get/set methods.
     */
    int getIonFd(buffer_handle_t handle, int *idx, int *num);
    int getBufInfo(buffer_handle_t handle, gralloc_buffer_info_t* bufInfo);
    int getSecureBuffer(buffer_handle_t handle, int *type, int *hBuffer);
    int setBufParameter(buffer_handle_t handle, int mask, int value);
    int getMVA(buffer_handle_t handle, void ** mvaddr);
    int setBufInfo(buffer_handle_t handle, const char * str);
private:
    friend class Singleton<GraphicBufferExtra>;

    GraphicBufferExtra();

    ~GraphicBufferExtra();

    extra_device_t *mExtraDev;
};

// ---------------------------------------------------------------------------
}; // namespace android

#endif // MTK_GRALLOC_EXTRA_GRAPHIC_BUFFER_EXTRA_H
