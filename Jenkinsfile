pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps { checkout scm }
        }

        stage('Coding Standards') {
            steps {
                // Runs clang-format on all .c and .h files
                // If it finds formatting issues, this will exit with 1 and fail the build
                sh 'find . -name "*.c" -o -name "*.h" | xargs clang-format --dry-run --Werror'
            }
        }

        stage('Static Analysis') {
            steps {
                // Runs Cppcheck and creates an XML report
                // --enable=all: checks everything
                // --xml: produces an XML file for Jenkins to read
                sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck-results.xml'
            }
        }

        stage('Build') {
            steps {
                sh 'make clean'
                sh 'make'
            }
        }
    }
    
    post {
        always {
            // Publishes the results of Cppcheck to the Jenkins dashboard
            publishCppcheck pattern: 'cppcheck-results.xml'
        }
    }
}