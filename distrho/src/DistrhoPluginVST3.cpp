#include "DistrhoPluginInternal.hpp"
#include "DistrhoDefines.h"
#include "travesty/audio_processor.h"
#include "travesty/edit_controller.h"
#include "travesty/factory.h"
#include "travesty/object.h"
#include "travesty/gen/iids.cpp"
#include <cstring>

START_NAMESPACE_DISTRHO

template <size_t N> void copyText8(char(& dst)[N], const char* src)
{
    strncpy(dst, src, N - 1);
    dst[N - 1] = '\0';
}

/**
 * processor
 */
class PluginProcessor : public v3::fobject,
                        public v3::audio_processor
{
public:
    static v3::fuid cid;

    V3_REFCOUNT_METHODS(fobject)
    V3_DEFINE_INTERFACES
    V3_DEF_INTERFACE(audio_processor)
    V3_END_DEFINE_INTERFACES(PluginProcessor)
};

v3::fuid PluginProcessor::cid = {};

/**
 * controller
 */
class PluginController : public v3::fobject,
                         public v3::edit_controller
{
public:
    static v3::fuid cid;

    V3_REFCOUNT_METHODS(fobject)
    V3_DEFINE_INTERFACES
    V3_DEF_INTERFACE(edit_controller)
    V3_END_DEFINE_INTERFACES(PluginController)
};

v3::fuid PluginController::cid = {};

/**
 * factory
 */
class PluginFactory : public v3::fobject,
                      public v3::plugin_factory
{
public:
    enum { kFactoryNumClasses = 2 };

    v3_factory_info fFactoryInfo {};
    v3_class_info fClassInfo[kFactoryNumClasses] {};

    static DISTRHO_NAMESPACE::PluginFactory* sInstance;

private:
    PluginFactory()
    {
        PluginExporter exporter(nullptr, nullptr);

        PluginProcessor::cid = v3::fuid(
            d_cconst('D', 'P', 'F', ' '), d_cconst('p', 'r', 'o', 'c'),
            0, exporter.getUniqueId());
        PluginController::cid = v3::fuid(
            d_cconst('D', 'P', 'F', ' '), d_cconst('c', 't', 'r', 'l'),
            0, exporter.getUniqueId());

        copyText8(fFactoryInfo.vendor, exporter.getMaker());
        copyText8(fFactoryInfo.url, exporter.getHomePage());
        copyText8(fFactoryInfo.email, ""); // TODO
        fFactoryInfo.flags = V3_FACTORY_UNICODE;

        v3_class_info& controller = fClassInfo[0];
        memcpy(controller.class_id, PluginController::cid.data, sizeof(v3_tuid));
        controller.cardinality = 0x7FFFFFFF;
        copyText8(controller.category, "Component Controller Class");
        copyText8(controller.name, DISTRHO_PLUGIN_NAME);

        v3_class_info& processor = fClassInfo[1];
        memcpy(processor.class_id, PluginProcessor::cid.data, sizeof(v3_tuid));
        processor.cardinality = 0x7FFFFFFF;
        copyText8(processor.category, "Audio Module Class");
        copyText8(processor.name, DISTRHO_PLUGIN_NAME);
    }

public:
    static PluginFactory* getInstance()
    {
        if (!sInstance)
            sInstance = new DISTRHO_NAMESPACE::PluginFactory;
        else
            sInstance->ref();
        return sInstance;
    }

    V3_API v3_result getFactoryInfo(struct v3_factory_info *info) override
    {
fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
        
        *info = fFactoryInfo;
        return V3_OK;
    }

    V3_API int32_t numClasses() override
    {
fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
        
        return kFactoryNumClasses;
    }

    V3_API v3_result getClassInfo(int32_t idx, struct v3_class_info *info) override
    {
fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
        
        if (idx < 0 || idx >= kFactoryNumClasses)
            return V3_FALSE;
        else
        {
            *info = fClassInfo[idx];
            return V3_OK;
        }
    }

    V3_API v3_result createInstance(const char *class_id, const char *_iid, void **instance) override
    {
fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
        
        return V3_FALSE;
    }

    V3_REFCOUNT_METHODS(fobject)
    V3_DEFINE_INTERFACES
    V3_DEF_INTERFACE(plugin_factory)
    V3_END_DEFINE_INTERFACES(PluginFactory)
};

PluginFactory* PluginFactory::sInstance = nullptr;

END_NAMESPACE_DISTRHO

/**
 * entry
 */
DISTRHO_PLUGIN_EXPORT
v3::plugin_factory* GetPluginFactory()
{
    return DISTRHO_NAMESPACE::PluginFactory::getInstance();
}
