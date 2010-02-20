#ifndef __BLIP_H
#define __BLIP_H
class Blip
{
        public:
                static Blip &get()
                {
                        static Blip me;
                        return me;
                }
                double duration;
                double ADSR(double t);
                int hue;
                int saturation;
                int normalValue;
                int inactiveAlpha;
                double freq[8];
                int delay;
                double echoDecay;
        private:
                Blip();
                double ADSR_linear(double t);
                void initFreqPentatonic();

                // next two to prevent accidental copying; no implementation for those.
                Blip(Blip const &);
                void operator=(Blip const &);
};
#endif
