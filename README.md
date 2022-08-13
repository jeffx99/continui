# Continui

An automatic continuo realization tool.

### Implementation
The rules of playing continuo are many but mostly straightforward; one can produce a passable result by blindly following a few important rules. Continui considers these rules and assigns a quantity called "badness" associated to breaking such rules. A search is then conducted over all reasonable realizations (up to a certain point in the future) to minimize badness.

**TODO**

- Refine penalty calculations
- Add another pass to include passing tones
- Use SDL and/or fluidsynth to render and playback visualization
