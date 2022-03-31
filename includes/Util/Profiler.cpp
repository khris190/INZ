#include "Profiler.hpp"

Profiler::Profiler()
{
}

Profiler *Profiler::getInstance() {
  if (!profiler)
    profiler = new Profiler;
  return profiler;
   }

void Profiler::AddSample(Sample sample)
{
    bool foundSample = false;

    for (size_t i = 0; i < samples.size(); i++)
    {
        if (sample.name == samples[i].name)
        {
            samples[i].nsTime += sample.nsTime;
            foundSample = true;
            break;
        }
    }
    if (!foundSample)
    {
        samples.push_back(sample);
    }
}

std::string Profiler::getTimingsAsString(bool doClearSamples)
{
    std::string retString;
    #ifdef DEBUG
    retString += "DEBUG TIMINGS!!!\n";
    #endif
    for (size_t i = 0; i < samples.size(); i++)
    {
        retString += samples[i].name + ": ";
        retString += std::to_string(samples[i].nsTime) + "ns.  ";
        retString += std::to_string(samples[i].nsTime / 1000000) + "ms.\n";
    }
    if (doClearSamples)
    {
        clearSamples();
    }
    return retString;
}

std::vector<Sample> Profiler::getTimings(bool doClearSamples)
{
    std::vector<Sample> retSample;

    for (size_t i = 0; i < samples.size(); i++)
    {
        retSample.push_back(Sample(samples[i].name, samples[i].nsTime));
    }
    if (doClearSamples)
    {
        clearSamples();
    }

    return retSample;
}

void Profiler::clearSamples()
{
    samples.clear();
}

void Profiler::printProfilerData(bool doClearSamples)
{
    for (size_t i = 0; i < samples.size(); i++)
    {
        std::cout << samples[i].name << ": " << samples[i].nsTime << "ns" << std::endl;
    }
    if (doClearSamples)
    {
        clearSamples();
    }
}

Profiler::~Profiler()
{
    clearSamples();
    if (profiler)
    {
        delete profiler;
    }
    
}

//Initialize pointer to zero so that it can be initialized in first call to getInstance
Profiler *Profiler::profiler = 0;


PTimer::PTimer(std::string name)
{
    sample.name = name;
    startTime = std::chrono::system_clock::now();
}

PTimer::~PTimer()
{
    sample.nsTime = std::chrono::duration<long, std::nano>(std::chrono::system_clock::now() - startTime).count();
    Profiler::getInstance()->AddSample(sample);
}
