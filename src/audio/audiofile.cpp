#include <featherkit/audio/audiofile.h>

namespace fea
{
            ALenum AudioFile::getFormat() const
            {
            }

            ALint AudioFile::getFrequency() const
            {
            }

            AudioData AudioFile::getSampleData() const
            {
            }

            void AudioFile::open(const std::string& path)
            {
                SF_INFO fileInfo;
                SNDFILE* file = sf_open(path.c_str(), SFM_READ, &fileInfo);
            }
}
