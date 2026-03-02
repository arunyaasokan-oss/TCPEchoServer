pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Coding Standards') {
            steps {
                // Using -print0 for safety with filenames
                sh 'find . -name "*.c" -o -name "*.h" -print0 | xargs -0 clang-format --dry-run --Werror'
            }
        }

        stage('Static Analysis') {
            steps {
                // Running cppcheck and saving the output
                sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck-results.xml'
            }
        }

        stage('Build') {
            steps {
                timestamps {
                    sh 'make clean'
                    sh 'make'
                }
            }
        }

        stage('Test') {
            steps {
                sh '''
                    ./server & 
                    SERVER_PID=$!
                    sleep 2
                    ./clienttest
                    kill $SERVER_PID
                '''
            }
        }
    }

    post {
        always {
            // This is the correct modern way to capture Cppcheck results
            recordIssues(
                enabledForFailure: true,
                tool: cppCheck(pattern: 'cppcheck-results.xml')
            )
            // Archive the actual binary created
            archiveArtifacts artifacts: 'clienttest', fingerprint: true
        }
    }
}