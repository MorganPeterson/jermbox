(import /build/jermbox :as jb)


(defer (jb/shutdown)
  (jb/init)	

  (def- row 0)
  (def- msg "press 'q' to quit")

  (jb/change-cell 0 row 0x2591 jb/white jb/red)

  (for col 0 (length msg)
    (jb/change-cell (+ 1 col) row (msg col) jb/black jb/green))

  (jb/change-cell (+ 1 (length msg)) row 0x2591 jb/white jb/red)

  (jb/present)
  (jb/poll-event (jb/init-event)))

