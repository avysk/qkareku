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
        private:
                Blip();
                double ADSR_linear(double t);

                // next two to prevent accidental copying; no implementation for those.
                Blip(Blip const &);
                void operator=(Blip const &);
};
