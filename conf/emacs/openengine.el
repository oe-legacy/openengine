;;
;; Emacs hacks for OpenEngine development.
;;

(defun path-parent (path)
  (let ((new-path (mapconcat 'identity
                             (butlast (split-string path "/"))
                             "/")))
    (if (equal (substring path 0 1) "/")
        (concat "/" new-path)
        new-path)))

(defun oe-find-make-path (path)
  (cond ((or (equal "/" path) (equal "" path)) nil)
        ((file-exists-p (concat path "/make.py")) path)
        (t (oe-find-make-path (path-parent path)))))

(defun is-upper (c)
  (and (>= c ?A)
       (<= c ?Z)))

(defun camel-to-caps (string)
  (upcase (apply 'concat (mapcar 
                  (lambda (ch)
                    (if (is-upper ch)
                        (concat "_" (char-to-string ch))
                      (char-to-string ch)))                    
                  string))))

(defun oe-new-file (file)
  ;; todo
  ;; - only add ifdef in .h files                                    
  (interactive "F")
  (find-file file)
  (let* ((make-path (oe-find-make-path (path-parent (buffer-file-name))))
         (namespace (car (last (split-string (path-parent file) "/"))))
         (filen (car (last (split-string (buffer-file-name) "/"))))         
         (dotparts (split-string filen "\\."))
         (class (car dotparts))
         (extension (cadr dotparts))         
         (isheader (string-equal "h" extension))
         (def-caps (camel-to-caps class)))    
    (when make-path
      ;; insert header
      (insert-file (concat make-path "/conf/HEADER"))
      (end-of-buffer)
      (insert 
              "\n\n")
      (if isheader
          (insert 
              "#ifndef _OE" def-caps "_H_\n"
              "#define _OE" def-caps "_H_\n"
              "\n\n")
        )
      (insert
              "namespace OpenEngine {\n"
              "namespace " namespace " {\n"
              "\n\n"
              "} // NS " namespace "\n" 
              "} // NS OpenEngine\n\n"
              )
      (if isheader
          (insert
              "#endif // _OE" def-caps "_H_\n"
              ))
      (beginning-of-buffer)
      (forward-char 3)
      (kill-line))))

(defun oe-doc ()
    (interactive)
    (insert "/**\n")
    (insert "*") (c-indent-command) (newline)
    (insert "*/") (c-indent-command) (newline-and-indent))

(defun oe-class ()
    (interactive)
    (let* ((file (car (last (split-string (buffer-file-name) "/"))))
           (class (car (split-string file "\\.")))
           (src-path (concat (oe-find-make-path (path-parent (buffer-file-name))) "/oe/"))
           (path (substring (buffer-file-name) (length src-path))))
      (insert "/**\n")
      (insert "* Short description.") (c-indent-command) (newline)
      (insert "*") (c-indent-command) (newline)
      (insert "* @class " class " " file " " path)
      (c-indent-command) (newline)
      (insert "*/") (c-indent-command) (newline)
      (insert "class " class " {\n"
              "private:\n\n"
              "public:\n")
      (c-indent-command)
      (insert "\n};") (c-indent-command)))

(defun oe-compile (&optional target)
  "Compile function that searches recursively backwards for a make.py
   script to invoke. If no script is found invokes `compile' in the
   default manner."
  (interactive)
  (let ((make-path (oe-find-make-path (path-parent (buffer-file-name)))))
    (if make-path
        ;; we want to close the compile window again if no errors occurred
        ;; just cant find the function right now :/
        (let ((my-buf (current-buffer))
              (com-buf (compile (concat "cd " make-path " && ./make.py " target " -k"))))
          (switch-to-buffer-other-window com-buf)
          (end-of-buffer)
          (switch-to-buffer-other-window my-buf))          
      ;; default to ordinary compile
      (call-interactively 'compile))))

(setq oe-compile-cont
      nil)
(setq oe-compile-arg
      nil)

(defun oe-compile-finished (buf state)
  (if oe-compile-cont
      (apply oe-compile-cont (list oe-compile-arg))))


(add-to-list 'compilation-finish-functions 'oe-compile-finished)

(defun oe-generate-tags ()
  "Generate a TAGS file for Emacs and add it to the tags table."
  (interactive)
  (let ((make-path (oe-find-make-path (path-parent (buffer-file-name)))))
    (when make-path
      (setq oe-compile-arg
            (concat make-path "/build/TAGS"))
       (setq oe-compile-cont
             (lambda (file)
               (visit-tags-table file)
               (setq oe-compile-cont nil)
               (setq oe-compile-arg nil)))
      (oe-compile "etags"))))



(add-hook 'c-mode-common-hook
  (lambda ()
    (local-set-key [(control c) (control v)] 'oe-compile)
    (local-set-key [(control c) (control r)]
                   (lambda () (interactive) (oe-compile "run")))
    (local-set-key [(control c) (control t)]
                   (lambda () (interactive) (oe-compile "testv")))
    (local-set-key [(control c) (control f)]
                   (lambda () (interactive) (oe-compile "doc")))))
