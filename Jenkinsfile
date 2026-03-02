pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                sh 'make clean'
                sh 'make'
            }
        }

        stage('Test') {
            steps {
                sh '''
                    # Start server in background
                    ./server & 
                    SERVER_PID=$!
                    
                    # Wait for server to be ready
                    sleep 2
                    
                    # Run the test binary (make sure this name matches!)
                    ./clienttest
                    
                    # Cleanup server
                    kill $SERVER_PID
                '''
            }
        }
    }

    // The post block MUST be outside the 'stages' block
    post {
        success {
            archiveArtifacts artifacts: 'clienttest', fingerprint: true
        }
    }
}