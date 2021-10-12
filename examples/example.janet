(import jermbox)

# Type character keys to see them displayed on the screen.
#
# Press 'q' to quit.

(defn command-loop
  []
  (label end
    (var env (jermbox/init-event))
    (while (jermbox/poll-event env)
      # 113 == letter 'q'
      (if (= (jermbox/event-character env) 113)
        (return end))
      (file/write stdout (string/from-bytes (jermbox/event-character env)))))
  (file/flush stdout))

(defn main [& args]
  (jermbox/init)
  (jermbox/select-output-mode jermbox/output-256)
  (jermbox/clear)
  (jermbox/present)
  (command-loop)
  (jermbox/shutdown))

