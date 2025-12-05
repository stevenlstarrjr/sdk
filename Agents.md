1. # HPainter Refactoring & Migration Plan

   **Version: 0.0.1a**

   ## Overview

   This document outlines the strategy for migrating from the legacy `HCanvas` API to the new, Qt-style `HPainter` interface. The goal is to modernize the drawing API, improve type safety with strict value types, and encapsulate backend complexities.

   ## Architectural Principles

   ### API Wrapping Strategy

   A critical decision has been made regarding how `HPainter` interacts with existing code during the transition.

   The Constraint: No Wrapping of Legacy Public APIs

   We must explicitly reject the approach of implementing HPainter as a "thin wrapper" over the existing HCanvas or HSurface API. While this might seem like an easier transitional step, it violates our core refactoring principles. Wrapping an old public API entrenchs the legacy behavior and prevents us from fixing underlying design flaws.

   The Directive: Wrap Third-Party APIs Only

   When refactoring, we adhere to the strict rule: We wrap third-party APIs, never our own old public APIs.

   Identification Rule: Legacy vs. Third-Party

   Before wrapping or refactoring a component, explicitly identify its origin to avoid "refactoring loops" where we accidentally wrap our own legacy abstractions.

   - **Third-Party:** Libraries like Qt, Skia, GLFW, Vulkan. **Action:** Wrap these directly.
   - **Legacy Internal:** Classes defined in this repository (e.g., `HSurface`, `WindowBase`, `HRenderWindow`). **Action:** Do NOT wrap these. You must bypass them, replace them, or extract the underlying third-party handles (e.g., raw `SkCanvas` or Vulkan swapchain handles) from them.

   Consequently, the implementation strategy is as follows:

   1. **Direct Implementation:** The new implementation must bypass `HSurface` entirely. It should directly wrap the underlying third-party APIs or system primitives (e.g., OpenGL, Qt, Skia, or OS-level drawing contexts).
   2. **Parallel Existence:** New and old paths will exist side-by-side during the migration. *(Note: This is not applicable until we hit our first beta version).*
   3. **Deprecation:** Once the backend directly wraps the native libraries, legacy callsites can be migrated. *(Note: This is not applicable until we hit our first beta version).*

   ## Implementation Progress & Steps

   ### Phase 1: Raster & Offscreen Rendering (Completed)

   The raster rendering path has been successfully refactored to wrap Skia directly, bypassing the legacy `HSurface`.

   - **Approach:** Added a Skia-backed raster render helper directly to `HImage`.
   - **Implementation:** `HImage::RenderRasterN32Premul` wraps `SkSurfaces::Raster` and `SkCanvas` directly.
   - **Outcome:** `HCanvas` is used strictly as a thin wrapper over `SkCanvas` for drawing commands, with no dependency on `HSurface`.
   - **Examples:** The `shapes_example.cpp` has been updated to remove `HSurface` includes and write PNGs via `HImage`.

   ### Phase 2: Windowing & GPU Rendering (Next Steps)

   The Vulkan/GPU windowing path currently remains dependent on `HSurface` acting as a swapchain wrapper. This must be refactored to align with the "Wrap Third-Party Only" rule.

   - **Current State:** `modules/graphics2d/examples/example1_vulkan.cpp` and windowing code call `window.getRenderSurface()` returning a `HSurface*`. This `WindowBase` is an internal legacy abstraction, not a third-party library.
   - **Action Plan:**
     1. **Bypass Legacy Windowing:** Do not attempt to "fix" `WindowBase` to use the new API if it inherently relies on `HSurface`. Instead, create a new windowing entry point or modify the windowing backend to expose raw Skia surfaces directly.
     2. **Direct Connection:** Implement a mechanism to obtain an `SkSurface`/`SkCanvas` directly from the OS Window/Vulkan swapchain.
     3. **Paint Entry:** Expose a `beginPaint(HPainter&)` (or similar) that initializes the `HPainter` with the raw Skia canvas, completely skipping `HSurface`.

   ### Phase 3: Cleanup & Types

   1. **Define Types:** Finalize the Qt-style value types (Point, Rect, Color, Pen, Brush) to replace `HSurface` structures.
   2. **Internalize/Remove:** Once Phase 2 is complete, `HSurface` should be entirely removed from the public API. It may be deleted or internalized strictly for private data management if absolutely necessary.
